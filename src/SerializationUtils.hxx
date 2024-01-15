
#pragma once

#include "SerializationUtils.hh"

namespace utils {

template<typename Enum>
inline auto serialize(std::ostream &out, const Enum &e) -> std::ostream &
{
  // https://www.reddit.com/r/cpp_questions/comments/30u26m/how_can_i_restrict_e_in_template_typename_e_to_be/
  static_assert(std::is_enum<Enum>::value, "Expected to be used with enums!");

  const auto eAsChar = reinterpret_cast<const char *>(e);
  const auto size    = sizeof(typename std::underlying_type<Enum>::type);
  for (auto id = 0u; id < size; ++id)
  {
    out.put(eAsChar[id]);
  }

  return out;
}

template<typename Enum>
inline auto deserialize(std::istream &in, Enum &e) -> std::istream &
{
  static_assert(std::is_enum<Enum>::value, "Expected to be used with enums!");

  const auto eAsChar = reinterpret_cast<char *>(e);
  const auto size    = sizeof(typename std::underlying_type<Enum>::type);
  for (auto id = 0u; id < size; ++id)
  {
    in >> eAsChar[id];
  }

  return in;
}

template<typename T, std::enable_if_t<std::is_enum<T>::value, bool> = true>
auto serialize(std::ostream &out, const std::optional<T> &value) -> std::ostream &
{
  out << value.has_value();
  if (value)
  {
    serialize(out, *value);
  }

  return out;
}

template<typename T, std::enable_if_t<!std::is_enum<T>::value, bool> = true>
auto serialize(std::ostream &out, const std::optional<T> &value) -> std::ostream &
{
  out << value.has_value();
  if (value)
  {
    out << *value;
  }

  return out;
}

template<typename T, std::enable_if_t<std::is_enum<T>::value, bool> = true>
auto deserialize(std::istream &in, std::optional<T> &value) -> std::istream &
{
  bool hasValue{false};
  in >> hasValue;
  if (hasValue)
  {
    T raw{};
    deserialize(in, raw);
    value = raw;
  }

  return in;
}

template<typename T, std::enable_if_t<!std::is_enum<T>::value, bool> = true>
auto deserialize(std::istream &in, std::optional<T> &value) -> std::istream &
{
  bool hasValue{false};
  in >> hasValue;
  if (hasValue)
  {
    T raw{};
    in >> raw;
    value = raw;
  }

  return in;
}

} // namespace utils
