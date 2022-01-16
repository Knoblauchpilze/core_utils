#ifndef    LOGGER_HH
# define   LOGGER_HH

# include <string>
# include "LogLevel.hh"

namespace utils {

  class Logger {
    public:

      virtual void
      setLevel(const Level& level) noexcept = 0;

      virtual void
      logMessage(const Level& level,
                 const std::string& message,
                 const std::string& module,
                 const std::string& service,
                 const std::string& cause = std::string()) const noexcept = 0;

      virtual void
      logError(const Level& level,
               const std::string& message,
               const std::string& cause,
               const std::string& module,
               const std::string& service) const noexcept = 0;
  };

}

#endif    /* LOGGER_HH */
