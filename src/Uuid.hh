#ifndef    UUID_HH
# define   UUID_HH

# include <string>
# include <vector>

namespace utils {

  class Uuid {
    public:

      Uuid();

      Uuid(const Uuid& uuid);

      Uuid&
      operator=(const Uuid& rhs) noexcept;

      bool
      operator==(const Uuid& rhs) const noexcept;

      bool
      operator!=(const Uuid& rhs) const noexcept;

      bool
      operator<(const Uuid& rhs) const noexcept;

      std::string
      toString() const noexcept;

      bool
      valid() const noexcept;

      void
      invalidate() noexcept;

      std::istream&
      operator>>(std::istream& in) noexcept;

      static
      Uuid
      create();

      static
      Uuid
      create(const std::string& uuid) noexcept;

    private:

      Uuid(const bool valid);

      void
      generate() noexcept;

    private:

      static constexpr const int sk_uuidLength = 32;

      /**
       * @brief - Contains the charset used to generate the
       *          identifiers.
       */
      static constexpr const char* sk_chars = "abcdef0123456789";

      static constexpr const int sk_charset = 16;

      /**
       * @brief - Defines the default string to represent an
       *          invalid uuid.
       */
      static constexpr const char* sk_invalidUuidString = "NaUuid";

      std::vector<uint8_t> m_data;
  };

}

std::ostream&
operator<<(std::ostream& out, const utils::Uuid& uuid) noexcept;

std::ostream&
operator<<(const utils::Uuid& uuid, std::ostream& out) noexcept;

std::istream&
operator>>(std::istream& in, utils::Uuid& id) noexcept;

# include "Uuid.hxx"
# include "Uuid_specialization.hxx"

#endif    /* UUID_HH */
