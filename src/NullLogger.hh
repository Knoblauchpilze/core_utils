#ifndef    NULL_LOGGER_HH
# define   NULL_LOGGER_HH

# include <mutex>
# include <string>
# include <memory>

# include "Logger.hh"

namespace utils {

  class NullLogger : public Logger {
    public:

      void
      setLevel(const Level& level) noexcept override;

      void
      logMessage(const Level& level,
                  const std::string& message,
                  const std::string& module,
                  const std::string& service,
                  const std::string& cause) const noexcept override;
  };

}

# include "NullLogger.hxx"

#endif    /* NULL_LOGGER_HH */
