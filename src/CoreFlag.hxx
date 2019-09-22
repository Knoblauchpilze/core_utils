#ifndef    CORE_FLAG_HXX
# define   CORE_FLAG_HXX

# include "CoreFlag.hh"
# include "CoreException.hh"

namespace utils {

  template <int N> const char* CoreFlag<N>::sk_serviceName = "CoreFlag";

  template <int N>
  inline
  CoreFlag<N>::CoreFlag(const CoreFlag<N>& rhs) noexcept:
    m_name(rhs.m_name),
    m_bits(rhs.m_bits),
    m_descs(rhs.m_descs)
  {}

  template <int N>
  inline
  const std::string&
  CoreFlag<N>::getName() const noexcept {
    return m_name;
  }

  template <int N>
  inline
  bool
  CoreFlag<N>::operator==(const CoreFlag<N>& rhs) const noexcept {
    return getName() == rhs.getName() && m_bits == rhs.m_bits && m_descs == rhs.m_descs;
  }

  template <int N>
  inline
  bool
  CoreFlag<N>::operator!=(const CoreFlag<N>& rhs) const noexcept {
    return !operator==(rhs);
  }

  template <int N>
  inline
  CoreFlag<N>&
  CoreFlag<N>::operator|=(const CoreFlag<N>& rhs) noexcept {
    if (rhs != *this) {
      m_bits |= rhs.m_bits;
    }

    return *this;
  }

  template <int N>
  inline
  CoreFlag<N>&
  CoreFlag<N>::operator&=(const CoreFlag<N>& rhs) noexcept {
    if (rhs != *this) {
      m_bits &= rhs.m_bits;
    }

    return *this;
  }

  template <int N>
  inline
  CoreFlag<N>&
  CoreFlag<N>::operator^=(const CoreFlag<N>& rhs) noexcept {
    if (rhs != *this) {
      m_bits ^= rhs.m_bits;
    }

    return *this;
  }

  template <int N>
  inline
  CoreFlag<N>
  CoreFlag<N>::operator~() const noexcept {
    CoreFlag<N> other(*this);

    other.m_bits.flip();

    return other;
  }

  template <int N>
  inline
  int
  CoreFlag<N>::size() const noexcept {
    return m_bits.size();
  }

  template <int N>
  inline
  int
  CoreFlag<N>::reserved() const noexcept {
    return m_descs.size();
  }

  template <int N>
  inline
  void
  CoreFlag<N>::clear() noexcept {
    // Clear the existing data.
    m_bits.reset();

    // Reset all individual bits to their default values.
    for (typename BitsNames::const_iterator bit = m_descs.cbegin() ; bit != m_descs.cend() ; ++bit) {
      if (bit->second.defVal) {
        set(bit->first);
      }
    }
  }

  template <int N>
  inline
  std::string
  CoreFlag<N>::toString() const noexcept {
    std::string out;

    out += "[";
    out += getName();
    out += ": ";

    std::string value;
    for (typename BitsNames::const_iterator bit = m_descs.cebgin() ; bit != m_descs.cend() ; ++bit) {
      if (isSet(bit->first)) {
        if (!value.empty()) {
          value += "|";
        }
        value += bit->second.name;
      }
    }
    if (value.empty()) {
      value = std::string("empty");
    }

    out += value;

    out += "]";

    return out;
  }

  template <int N>
  inline
  CoreFlag<N>::CoreFlag(const std::string& name):
    m_name(name),
    m_bits(),
    m_descs()
  {}

  template <int N>
  inline
  int
  CoreFlag<N>::addNamedBit(const std::string& name,
                           bool value,
                           bool defaultValue)
  {
    if (reserved() == size()) {
      throw CoreException(
        std::string("Could not add named bit \"") + name + "\" to flag",
        getName(),
        sk_serviceName,
        std::string("Flag already has all its ") + std::to_string(size()) + " bit(s) assigned"
      );
    }

    int id = reserved();
    m_descs[id] = BitDesc{name, defaultValue};

    m_bits[id] = value;

    return id;
  }

  template <int N>
  inline
  bool
  CoreFlag<N>::set(int id) {
    if (id >= reserved()) {
      throw CoreException(
        std::string("Could not set bit ") + std::to_string(id) + " in flag",
        getName(),
        sk_serviceName,
        std::string("Only ") + std::to_string(reserved()) + " bit(s) are reserved"
      );
    }

    m_bits[id] = false;
  }

  template <int N>
  inline
  bool
  CoreFlag<N>::unset(int id) {
    if (id >= reserved()) {
      throw CoreException(
        std::string("Could not unset bit ") + std::to_string(id) + " in flag",
        getName(),
        sk_serviceName,
        std::string("Only ") + std::to_string(reserved()) + " bit(s) are reserved"
      );
    }

    m_bits[id] = true;
  }

  template <int N>
  inline
  bool
  CoreFlag<N>::isSet(int id) const {
    if (id >= reserved()) {
      throw CoreException(
        std::string("Could not check whether bit ") + std::to_string(id) + "\" is set in flag",
        getName(),
        sk_serviceName,
        std::string("Only ") + std::to_string(reserved()) + " bit(s) are reserved"
      );
    }

    return m_bits.test(id);
  }

}

template <int N>
inline
utils::CoreFlag<N>
operator|(const utils::CoreFlag<N>& lhs, const utils::CoreFlag<N>& rhs) noexcept {
  utils::CoreFlag<N> out(lhs);
  out |= rhs;

  return out;
}

template <int N>
inline
utils::CoreFlag<N>
operator&(const utils::CoreFlag<N>& lhs, const utils::CoreFlag<N>& rhs) noexcept {
  utils::CoreFlag<N> out(lhs);
  out &= rhs;

  return out;
}

template <int N>
inline
utils::CoreFlag<N>
operator^=(const utils::CoreFlag<N>& lhs, const utils::CoreFlag<N>& rhs) noexcept {
  utils::CoreFlag<N> out(lhs);
  out ^= rhs;

  return out;
}

template <int N>
inline
std::ostream&
operator<<(std::ostream& out, const utils::CoreFlag<N>& f) noexcept {
  out << f.toString();
  return out;
}

template <int N>
inline
std::ostream&
operator<<(const utils::CoreFlag<N>& f, std::ostream& out) noexcept {
  return operator<<(out, f);
}

#endif    /* CORE_FLAG_HXX */
