#ifndef    UUID_HH
# define   UUID_HH

# include <string>
# include <vector>

namespace utils {

  class Uuid {
    public:

      Uuid();

      Uuid(const Uuid& uuid) = delete;

      Uuid&
      operator=(const Uuid& rhs) = delete;

      bool
      operator==(const Uuid& rhs) const noexcept;

      bool
      operator!=(const Uuid& rhs) const noexcept;

      bool
      operator<(const Uuid& rhs) const noexcept;

      std::string
      toString() const noexcept;

    private:

      void
      create() noexcept;

    private:

      static const int sk_uuidLength = 32;

      std::vector<uint8_t> m_data;
  };

}

std::ostream&
operator<<(const utils::Uuid& uuid, std::ostream& out) noexcept;

std::ostream&
operator<<(std::ostream& out, const utils::Uuid& uuid) noexcept;

# include "Uuid.hxx"

#endif    /* UUID_HH */