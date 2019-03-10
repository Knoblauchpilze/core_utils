#ifndef    CORE_LOG_LEVEL_HH
# define   CORE_LOG_LEVEL_HH

# include <string>

namespace utils {
  namespace core {

    // Various levels of logs.
    enum class Level {
      Debug,
      Info,
      Notice,
      Warning,
      Error,
      Critical,
      Fatal
    };

    Level
    convertLevelStringToLevel(const Level& level) noexcept;

    std::string
    convertLevelToLevelString(const Level& level);

  }
}

# include "CoreLogLevel.hxx"

#endif    /* CORE_LOG_LEVEL_HH */
