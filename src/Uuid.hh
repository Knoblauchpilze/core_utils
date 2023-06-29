
#pragma once

#include <string>
#include <vector>

namespace utils {

class Uuid {
public:
  Uuid();

  Uuid(const Uuid &uuid);

  Uuid &operator=(const Uuid &rhs) noexcept;

  bool operator==(const Uuid &rhs) const noexcept;

  bool operator!=(const Uuid &rhs) const noexcept;

  bool operator<(const Uuid &rhs) const noexcept;

  auto toString() const noexcept -> std::string;

  bool valid() const noexcept;

  void invalidate() noexcept;

  auto operator>>(std::istream &in) noexcept -> std::istream &;

  static auto create() -> Uuid;

  static auto create(const std::string &uuid) noexcept -> Uuid;

private:
  Uuid(const bool valid);

  void generate() noexcept;

private:
  static constexpr const int sk_uuidLength = 32;

  /// @brief - Contains the charset used to generate the identifiers.
  static constexpr const char *sk_chars = "abcdef0123456789";
  static constexpr const int sk_charset = 16;

  /// @brief - Defines the default string to represent an invalid uuid.
  static constexpr const char *sk_invalidUuidString = "NaUuid";

  std::vector<uint8_t> m_data;
};

} // namespace utils

std::ostream &operator<<(std::ostream &out, const utils::Uuid &uuid) noexcept;

std::ostream &operator<<(const utils::Uuid &uuid, std::ostream &out) noexcept;

std::istream &operator>>(std::istream &in, utils::Uuid &id) noexcept;

#include "Uuid.hxx"
#include "Uuid_specialization.hxx"
