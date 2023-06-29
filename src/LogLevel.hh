
#pragma once

#include <string>

namespace utils {

enum class Level {
  Verbose,
  Debug,
  Info,
  Warning,
  Notice,
  Error,
  Critical,
  Fatal
};

auto convertLevelStringToLevel(const std::string &level) noexcept -> Level;
auto convertLevelToLevelString(const Level level) -> std::string;

} // namespace utils

#include "LogLevel.hxx"
