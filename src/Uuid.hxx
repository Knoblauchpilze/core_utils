#ifndef    UUID_HXX
# define   UUID_HXX

# include "Uuid.hh"
# include <random>

namespace utils {

  inline
  Uuid::Uuid():
    m_data(sk_uuidLength)
  {
    create();
  }

  inline
  bool
  Uuid::operator==(const Uuid& rhs) const noexcept {
    return !operator!=(rhs);
  }

  inline
  bool
  Uuid::operator!=(const Uuid& rhs) const noexcept {
    unsigned index = 0u;
    while (index < m_data.size() && m_data[index] == rhs.m_data[index]) {
      ++index;
    }

    if (index >= m_data.size()) {
      return false;
    }

    return m_data[index] == rhs.m_data[index];
  }

  inline
  bool
  Uuid::operator<(const Uuid& rhs) const noexcept {
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

    return display;
  }

  inline
  void
  Uuid::create() noexcept {
    std::string chars = "abcdef0123456789";

    std::random_device seed;
    std::default_random_engine re(seed());
    std::uniform_int_distribution<int> rng(0, chars.size());

    // Generate something like: "47183823-2574-4bfd-b411-99ed177d3e43"
    for (unsigned index = 0u ; index < m_data.size() ; ++index) {
      m_data[index] = chars[rng(re)];
    }
  }

}

std::ostream&
operator<<(const utils::Uuid& uuid, std::ostream& out) noexcept {
  return operator<<(out, uuid);
}

std::ostream&
operator<<(std::ostream& out, const utils::Uuid& uuid) noexcept {
  out << uuid.toString();
  return out;
}


#endif    /* UUID_HXX */
