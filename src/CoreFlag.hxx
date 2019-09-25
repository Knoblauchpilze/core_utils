#ifndef    CORE_FLAG_HXX
# define   CORE_FLAG_HXX

# include "CoreFlag.hh"
# include "CoreException.hh"

namespace utils {

  template <typename Enum>
  inline
  std::string
  getNameForKey(const Enum& key) {
    static_assert(std::is_enum<Enum>::value, "Must be an enum type");

    // Not defined at the general level, should be specialized for each
    // enumeration to be used with the `CoreFlag` class.
    throw CoreException(
      std::string("Could not get name for key ") + std::to_string(static_cast<typename std::underlying_type<Enum>::value>(key)),
      std::string("CoreFlag"),
      std::string("getNameForKey"),
      std::string("No valid template specialization")
    );
  }

  template <typename Enum> const char* CoreFlag<Enum>::sk_serviceName = "CoreFlag";

  template <typename Enum>
  inline
  CoreFlag<Enum>::CoreFlag():
    m_name(typeid(Enum).name()),
    m_bits(),
    m_descs()
  {
    init();
  }

  template <typename Enum>
  inline
  CoreFlag<Enum>::CoreFlag(const Enum& value):
    // TODO: This typeid business produces names like so: "[N3sdl4core5focus4TypeE: Click]"
    // which is not exactly human readable. Maybe we should rely on the `abi` interface.
    m_name(typeid(Enum).name()),
    m_bits(),
    m_descs()
  {
    init();

    set(value);
  }

  template <typename Enum>
  inline
  CoreFlag<Enum>::CoreFlag(const CoreFlag<Enum>& rhs) noexcept:
    m_name(rhs.m_name),
    m_bits(rhs.m_bits),
    m_descs(rhs.m_descs)
  {}

  template <typename Enum>
  inline
  const std::string&
  CoreFlag<Enum>::getName() const noexcept {
    return m_name;
  }

  template <typename Enum>
  inline
  bool
  CoreFlag<Enum>::operator==(const CoreFlag<Enum>& rhs) const noexcept {
    if (getName() != rhs.getName()) {
      return false;
    }

    // Given that the bits are registered upon building this object and
    // provided that we only consider equality between elements which
    // define the same template enumeration it seems overkill to check
    // individual fields. Indeed we will have registered elements in the
    // same order while constructing the object so we will consider us
    // happy with only checking that the internal bits are identical.
    return m_bits == rhs.m_bits;
  }

  template <typename Enum>
  inline
  bool
  CoreFlag<Enum>::operator==(const Enum& key) const noexcept {
    return isSet(key);
  }

  template <typename Enum>
  inline
  bool
  CoreFlag<Enum>::operator!=(const CoreFlag<Enum>& rhs) const noexcept {
    return !operator==(rhs);
  }

  template <typename Enum>
  inline
  bool
  CoreFlag<Enum>::operator!=(const Enum& key) const noexcept {
    return !operator==(key);
  }

  template <typename Enum>
  inline
  CoreFlag<Enum>&
  CoreFlag<Enum>::operator|=(const CoreFlag<Enum>& rhs) noexcept {
    if (rhs != *this) {
      m_bits |= rhs.m_bits;
    }

    return *this;
  }

  template <typename Enum>
  inline
  CoreFlag<Enum>&
  CoreFlag<Enum>::operator|=(const Enum& key) noexcept {
    set(key);

    return *this;
  }

  template <typename Enum>
  inline
  CoreFlag<Enum>&
  CoreFlag<Enum>::operator&=(const CoreFlag<Enum>& rhs) noexcept {
    if (rhs != *this) {
      m_bits &= rhs.m_bits;
    }

    return *this;
  }

  template <typename Enum>
  inline
  CoreFlag<Enum>&
  CoreFlag<Enum>::operator&=(const Enum& key)  noexcept {
    // We want to keep only the bit corresponding to `key`
    // active if it was the case and none if it wasn't.
    const bool v = isSet(key);
    clear();
    if (v) {
      set(key);
    }

    return *this;
  }

  template <typename Enum>
  inline
  CoreFlag<Enum>&
  CoreFlag<Enum>::operator^=(const CoreFlag<Enum>& rhs) noexcept {
    if (rhs != *this) {
      m_bits ^= rhs.m_bits;
    }

    return *this;
  }

  template <typename Enum>
  inline
  CoreFlag<Enum>&
  CoreFlag<Enum>::operator^=(const Enum& key) noexcept {
    // We want to keep only the bit which are exclusively
    // inside `this` OR inside `key`. Everything except the
    // `key` bit will thus be preserved, and also the `key`
    // bit will be set if it was not already in which case
    // it will be turned off.
    if (isSet(key)) {
      unset(key);
    }

    return *this;
  }

  template <typename Enum>
  inline
  CoreFlag<Enum>
  CoreFlag<Enum>::operator~() const noexcept {
    CoreFlag<Enum> other(*this);

    other.m_bits.flip();

    return other;
  }

  template <typename Enum>
  inline
  int
  CoreFlag<Enum>::size() const noexcept {
    return m_bits.size();
  }

  template <typename Enum>
  inline
  int
  CoreFlag<Enum>::reserved() const noexcept {
    return m_descs.size();
  }

  template <typename Enum>
  inline
  bool
  CoreFlag<Enum>::set(const Enum& key) {
    // Attempt to retrieve the index for this key.
    int id = getIdFor(key);

    // Check for errors.
    if (id < 0) {
      throw CoreException(
        std::string("Could not set bit ") + getNameForKey(key) + " in flag",
        getName(),
        sk_serviceName,
        std::string("Associated bit not found")
      );
    }

    m_bits[id] = true;
  }

  template <typename Enum>
  inline
  bool
  CoreFlag<Enum>::unset(const Enum& key) {
    // Attempt to retrieve the index for this key.
    int id = getIdFor(key);

    // Check for errors.
    if (id < 0) {
      throw CoreException(
        std::string("Could not unset bit ") + getNameForKey(key) + " in flag",
        getName(),
        sk_serviceName,
        std::string("Associated bit not found")
      );
    }

    m_bits[id] = false;
  }

  template <typename Enum>
  inline
  bool
  CoreFlag<Enum>::isSet(const Enum& key) const {
    // Attempt to retrieve the index for this key.
    int id = getIdFor(key);

    // Check for errors.
    if (id < 0) {
      throw CoreException(
        std::string("Could not check whether bit ") + getNameForKey(key) + " is set in flag",
        getName(),
        sk_serviceName,
        std::string("Associated bit not found")
      );
    }

    return m_bits.test(id);
  }

  template <typename Enum>
  inline
  void
  CoreFlag<Enum>::clear() noexcept {
    // Clear the existing data.
    m_bits.reset();

    // Reset all individual bits to their default values.
    for (typename BitsIDs::const_iterator bit = m_descs.cbegin() ; bit != m_descs.cend() ; ++bit) {
      if (bit->second.defVal) {
        set(bit->first);
      }
    }
  }

  template <typename Enum>
  inline
  std::string
  CoreFlag<Enum>::toString() const noexcept {
    std::string out;

    out += "[";
    out += getName();
    out += ": ";

    std::string value;
    for (typename BitsIDs::const_iterator bit = m_descs.cbegin() ; bit != m_descs.cend() ; ++bit) {
      if (isSet(bit->first)) {
        if (!value.empty()) {
          value += "|";
        }
        // Note: we rely on the existence of a method in the `utils` namespace which
        // allows to convert the name of the enumeration into a valid string.
        value += getNameForKey(bit->first);
      }
    }
    if (value.empty()) {
      value = std::string("empty");
    }

    out += value;

    out += "]";

    return out;
  }

  template <typename Enum>
  inline
  void
  CoreFlag<Enum>::init() {
    FlagType count = FlagType(0);
    FlagType max = static_cast<FlagType>(Enum::ValuesCount);
    while (count < max) {
      addBit(static_cast<Enum>(count), false, false);
      ++count;
    }
  }

  template <typename Enum>
  inline
  int
  CoreFlag<Enum>::getIdFor(const Enum& key) const noexcept {
    typename BitsIDs::const_iterator bit = m_descs.find(key);

    if (bit == m_descs.cend()) {
      return -1;
    }

    return bit->second.id;
  }

  template <typename Enum>
  inline
  int
  CoreFlag<Enum>::addBit(const Enum& key,
                         bool value,
                         bool defaultValue)
  {
    if (reserved() == size()) {
      throw CoreException(
        std::string("Could not add bit \"") + getNameForKey(key) + "\" to flag",
        getName(),
        sk_serviceName,
        std::string("Flag already has all its ") + std::to_string(size()) + " bit(s) assigned"
      );
    }

    int id = reserved();
    m_descs[key] = BitDesc{id, defaultValue};

    m_bits[id] = value;

    return id;
  }

}

template <typename Enum>
inline
utils::CoreFlag<Enum>
operator|(const utils::CoreFlag<Enum>& lhs, const utils::CoreFlag<Enum>& rhs) noexcept {
  utils::CoreFlag<Enum> out(lhs);
  out |= rhs;

  return out;
}

template <typename Enum>
inline
utils::CoreFlag<Enum>
operator&(const utils::CoreFlag<Enum>& lhs, const utils::CoreFlag<Enum>& rhs) noexcept {
  utils::CoreFlag<Enum> out(lhs);
  out &= rhs;

  return out;
}

template <typename Enum>
inline
utils::CoreFlag<Enum>
operator^=(const utils::CoreFlag<Enum>& lhs, const utils::CoreFlag<Enum>& rhs) noexcept {
  utils::CoreFlag<Enum> out(lhs);
  out ^= rhs;

  return out;
}

template <typename Enum>
inline
std::ostream&
operator<<(std::ostream& out, const utils::CoreFlag<Enum>& f) noexcept {
  out << f.toString();
  return out;
}

template <typename Enum>
inline
std::ostream&
operator<<(const utils::CoreFlag<Enum>& f, std::ostream& out) noexcept {
  return operator<<(out, f);
}

#endif    /* CORE_FLAG_HXX */
