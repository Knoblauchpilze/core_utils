#ifndef    UUID_HXX
# define   UUID_HXX

# include "Uuid.hh"
# include <random>
# include <istream>

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
  std::istream&
  Uuid::operator>>(std::istream& in) noexcept {
    constexpr unsigned expected = sk_uuidLength + 4 + 1;
    char raw[expected];

    in.get(raw, expected);

    // Send this string to the creation method.
    Uuid id = create(raw);
    operator=(id);

    return in;
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
  Uuid
  Uuid::create(const std::string& uuid) noexcept {
    // Generate an identifier from the first `sk_uuidLength`
    // valid characters from the string. In case the string
    // does not seem valid we will return an invalid uuid.
    // Corresponds to the uuid and the separating `-` chars.
    unsigned expected = sk_uuidLength + 4u;

    if (uuid.size() != expected) {
      return Uuid();
    }

    Uuid id;
    id.m_data.resize(sk_uuidLength);

    // Interpret a string like the following one:
    // `47183823-2574-4bfd-b411-99ed177d3e43`.
    for (unsigned index = 0u ; index < expected ; ++index) {
      // Prevent interpretation of `-` characters.
      if (index == 8u || index == 13u || index == 18u || index == 23u) {
        continue;
      }

      // Offset to account for `-` characters.
      unsigned i = index;
      if (index > 8u) {
        --i;
      }
      if (index > 13u) {
        --i;
      }
      if (index > 18u) {
        --i;
      }
      if (index > 23u) {
        --i;
      }

      // Interpret the character knowing that the
      // charset is "abcdef0123456789".
      char a = uuid[index];

      id.m_data[i] = 'a';

      if (a >= 'a' && a <= 'f') {
        id.m_data[i] = a;
      }
      if (a >= '0' && a <= '9') {
        id.m_data[i] = a;
      }
    }

    return id;
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

inline
std::istream&
operator>>(std::istream& in, utils::Uuid& id) noexcept {
  id >> in;
  return in;
}

#endif    /* UUID_HXX */
