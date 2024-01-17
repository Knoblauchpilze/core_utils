
#pragma once

#include "SerializationUtils.hh"

namespace utils {

template<typename T, std::enable_if_t<std::is_enum<T>::value, bool> = true>
inline auto serialize(std::ostream &out, const T &e) -> std::ostream &
{
  const auto eAsChar = reinterpret_cast<const char *>(&e);
  const auto size    = sizeof(typename std::underlying_type<T>::type);
  out.write(eAsChar, size);

  return out;
}

template<typename T, std::enable_if_t<!std::is_enum<T>::value, bool> = true>
inline auto serialize(std::ostream &out, const T &value) -> std::ostream &
{
  const auto valueAsChar = reinterpret_cast<const char *>(&value);
  const auto size        = sizeof(T);
  out.write(valueAsChar, size);

  return out;
}

template<typename T, std::enable_if_t<std::is_enum<T>::value, bool> = true>
inline auto deserialize(std::istream &in, T &e) -> std::istream &
{
  const auto eAsChar = reinterpret_cast<char *>(&e);
  const auto size    = sizeof(typename std::underlying_type<T>::type);
  in.read(eAsChar, size);

  return in;
}

template<typename T, std::enable_if_t<!std::is_enum<T>::value, bool> = true>
inline auto deserialize(std::istream &in, T &value) -> std::istream &
{
  const auto valueAsChar = reinterpret_cast<char *>(&value);
  const auto size        = sizeof(T);
  in.read(valueAsChar, size);

  return in;
}

inline auto serialize(std::ostream &out, const std::string &str) -> std::ostream &
{
  const std::size_t size{str.size()};
  out.write(reinterpret_cast<const char *>(&size), sizeof(std::size_t));
  if (!str.empty())
  {
    out << str;
  }

  return out;
}

inline auto deserialize(std::istream &in, std::string &str) -> std::istream &
{
  std::size_t size{};
  in.read(reinterpret_cast<char *>(&size), sizeof(std::size_t));
  str.resize(size);
  in.read(str.data(), size);

  return in;
}

template<typename T, std::enable_if_t<std::is_enum<T>::value, bool> = true>
inline auto serialize(std::ostream &out, const std::optional<T> &value) -> std::ostream &
{
  const auto hasValue = value.has_value();
  out.write(reinterpret_cast<const char *>(&hasValue), sizeof(bool));
  if (hasValue)
  {
    serialize(out, *value);
  }

  return out;
}

template<typename T, std::enable_if_t<!std::is_enum<T>::value, bool> = true>
inline auto serialize(std::ostream &out, const std::optional<T> &value) -> std::ostream &
{
  const auto hasValue = value.has_value();
  out.write(reinterpret_cast<const char *>(&hasValue), sizeof(bool));
  if (hasValue)
  {
    serialize(out, *value);
  }

  return out;
}

template<typename T, std::enable_if_t<std::is_enum<T>::value, bool> = true>
inline auto deserialize(std::istream &in, std::optional<T> &value) -> std::istream &
{
  bool hasValue{false};
  in.read(reinterpret_cast<char *>(&hasValue), sizeof(bool));
  if (hasValue)
  {
    T raw{};
    deserialize(in, raw);
    value = raw;
  }
  else
  {
    value.reset();
  }

  return in;
}

template<typename T, std::enable_if_t<!std::is_enum<T>::value, bool> = true>
inline auto deserialize(std::istream &in, std::optional<T> &value) -> std::istream &
{
  bool hasValue{false};
  in.read(reinterpret_cast<char *>(&hasValue), sizeof(bool));
  if (hasValue)
  {
    T raw{};
    deserialize(in, raw);
    value = raw;
  }
  else
  {
    value.reset();
  }

  return in;
}

} // namespace utils
