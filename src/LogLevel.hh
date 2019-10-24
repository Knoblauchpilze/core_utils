#ifndef    LOG_LEVEL_HH
# define   LOG_LEVEL_HH

# include <string>

namespace utils {

  // Various levels of logs.
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

  Level
  convertLevelStringToLevel(const Level& level) noexcept;

  std::string
  convertLevelToLevelString(const Level& level);

}

# include "LogLevel.hxx"

#endif    /* LOG_LEVEL_HH */
