#ifndef    UUID_HXX
# define   UUID_HXX

# include "Uuid.hh"
# include <random>

namespace utils {

  inline
  Uuid::Uuid():
    m_data()
  {}

  inline
  Uuid::Uuid(const Uuid& uuid):
    m_data(uuid.m_data)
  {}

  inline
  Uuid&
  Uuid::operator=(const Uuid& rhs) noexcept {
    if (rhs != *this) {
      m_data = rhs.m_data;
    }

    return *this;
  }

  inline
  bool
  Uuid::operator==(const Uuid& rhs) const noexcept {
    // Check for invalid uuids.
    if (!valid() && !rhs.valid()) {
      return true;
    }
    if (valid() && !rhs.valid()) {
      return false;
    }
    if (!valid() && rhs.valid()) {
      return false;
    }

    unsigned index = 0u;
    while (index < m_data.size() && m_data[index] == rhs.m_data[index]) {
      ++index;
    }

    if (index >= m_data.size()) {
      return true;
    }

    return m_data[index] == rhs.m_data[index];
  }

  inline
  bool
  Uuid::operator!=(const Uuid& rhs) const noexcept {
    return !operator==(rhs);
  }

  inline
  bool
  Uuid::operator<(const Uuid& rhs) const noexcept {
    // Check for invalid uuids.
    if (!valid() && !rhs.valid()) {
      return false;
    }
    if (valid() && !rhs.valid()) {
      return false;
    }
    if (!valid() && rhs.valid()) {
      return true;
    }

    unsigned index = 0u;
    while (index < m_data.size() && m_data[index] < rhs.m_data[index]) {
      ++index;
    }

    if (index >= m_data.size()) {
      return false;
    }

    return m_data[index] < rhs.m_data[index];
  }

  inline
  std::string
  Uuid::toString() const noexcept {
    std::string display;

    for (unsigned index = 0u ; index < m_data.size() ; ++index) {
      display += m_data[index];
      if (index == 7u || index == 11u || index == 15u || index == 19u) {
        display += "-";
      }
    }

    if (!valid()) {
      display += "NaUuid";
    }

    return display;
  }

  inline
  void
  Uuid::invalidate() noexcept {
    m_data.clear();
  }

  inline
  bool
  Uuid::valid() const noexcept {
    return !m_data.empty();
  }

  inline
  Uuid
  Uuid::create() {
    return Uuid(true);
  }

  inline
  Uuid::Uuid(const bool /*valid*/):
    m_data(sk_uuidLength)
  {
    generate();
  }

  inline
  void
  Uuid::generate() noexcept {
    std::random_device seed;
    std::default_random_engine re(seed());
    std::uniform_int_distribution<int> rng(0, sk_charset - 1);

    // Generate something like: "47183823-2574-4bfd-b411-99ed177d3e43"
    for (unsigned index = 0u ; index < m_data.size() ; ++index) {
      m_data[index] = sk_chars[rng(re)];
    }
  }

}

inline
std::ostream&
operator<<(std::ostream& out, const utils::Uuid& uuid) noexcept {
  out << uuid.toString();
  return out;
}

inline
std::ostream&
operator<<(const utils::Uuid& uuid, std::ostream& out) noexcept {
  return operator<<(out, uuid);
}


#endif    /* UUID_HXX */
