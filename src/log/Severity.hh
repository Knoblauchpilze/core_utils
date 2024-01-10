
#pragma once

#include <string>

namespace utils::log {

enum class Severity
{
  VERBOSE,
  DEBUG,
  INFO,
  WARNING,
  NOTICE,
  ERROR
};

auto fromStr(const std::string &severity) noexcept -> Severity;
auto str(const Severity severity) -> std::string;

} // namespace utils::log
