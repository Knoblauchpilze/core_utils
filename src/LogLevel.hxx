
#pragma once

#include "LogLevel.hh"

namespace utils {

inline auto convertLevelStringToLevel(const std::string &level) noexcept
    -> Level {
  if (level == "fatal") {
    return Level::Fatal;
  } else if (level == "critical") {
    return Level::Critical;
  } else if (level == "error") {
    return Level::Error;
  } else if (level == "warning") {
    return Level::Warning;
  } else if (level == "notice") {
    return Level::Notice;
  } else if (level == "info") {
    return Level::Info;
  } else if (level == "debug") {
    return Level::Debug;
  } else {
    // Assume verbose.
    return Level::Verbose;
  }
}

inline auto convertLevelToLevelString(const Level level) -> std::string {
  switch (level) {
  case Level::Fatal:
    return "fatal";
  case Level::Critical:
    return "critical";
  case Level::Error:
    return "error";
  case Level::Warning:
    return "warning";
  case Level::Notice:
    return "notice";
  case Level::Info:
    return "info";
  case Level::Debug:
    return "debug";
  case Level::Verbose:
  default:
    return "verbose";
  }
}

} // namespace utils
