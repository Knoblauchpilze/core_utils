
#pragma once

#include <istream>
#include <ostream>
#include <type_traits>

namespace utils {

template<typename Enum>
auto serialize(std::ostream &out, const Enum &e) -> std::ostream &;

template<typename Enum>
auto deserialize(std::istream &in, Enum &e) -> std::istream &;

} // namespace utils

#include "SerializationUtils.hxx"
