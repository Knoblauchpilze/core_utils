#ifndef    CORE_LOG_LEVEL_HXX
# define   CORE_LOG_LEVEL_HXX

# include "CoreLogLevel.hh"

namespace core {
  namespace utils {

    inline
    Level
    convertLevelStringToLevel(const std::string& level) noexcept {
      if (level == "fatal") {
        return Level::Fatal;
      }
      else if (level == "critical") {
        return Level::Critical;
      }
      else if (level == "error") {
        return Level::Error;
      }
      else if (level == "warning") {
        return Level::Warning;
      }
      else if (level == "notice") {
        return Level::Notice;
      }
      else if (level == "info") {
        return Level::Info;
      }
      else {
        // Assume debug.
        return Level::Debug;
      }
    }

    inline
    std::string
    convertLevelToLevelString(const Level& level) {
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
        default:
          return "debug";
      }
    }

  }
}

#endif    /* CORE_LOG_LEVEL_HXX */
