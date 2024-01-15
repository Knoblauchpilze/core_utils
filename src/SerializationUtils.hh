
#pragma once

#include <istream>
#include <optional>
#include <ostream>
#include <type_traits>

namespace utils {

template<typename Enum>
auto serialize(std::ostream &out, const Enum &e) -> std::ostream &;

template<typename Enum>
auto deserialize(std::istream &in, Enum &e) -> std::istream &;

/// https://stackoverflow.com/questions/55647741/template-specialization-with-enable-if
/// https://en.cppreference.com/w/cpp/types/enable_if

template<typename T, std::enable_if_t<std::is_enum<T>::value, bool> = true>
auto serialize(std::ostream &out, const std::optional<T> &value) -> std::ostream &;

template<typename T, std::enable_if_t<!std::is_enum<T>::value, bool> = true>
auto serialize(std::ostream &out, const std::optional<T> &value) -> std::ostream &;

template<typename T, std::enable_if_t<std::is_enum<T>::value, bool> = true>
auto deserialize(std::istream &in, std::optional<T> &value) -> std::istream &;

template<typename T, std::enable_if_t<!std::is_enum<T>::value, bool> = true>
auto deserialize(std::istream &in, std::optional<T> &value) -> std::istream &;

} // namespace utils

#include "SerializationUtils.hxx"
