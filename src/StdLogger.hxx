#ifndef    STD_LOGGER_HXX
# define   STD_LOGGER_HXX

# include "StdLogger.hh"
# include <sstream>
# include <iomanip>

namespace utils {

  inline
  void
  StdLogger::setLevel(const Level& level) noexcept {
    std::lock_guard<std::mutex> lock(m_locker);
    m_level = level;
  }

  inline
  void
  StdLogger::logMessage(const Level& level,
                        const std::string& message,
                        const std::string& module,
                        const std::string& service,
                        const std::string& cause) const noexcept
  {
    switch (level) {
      case Level::Verbose:
        logVerbose(message, module, service, cause);
        break;
      case Level::Debug:
        logDebug(message, module, service, cause);
        break;
      case Level::Info:
        logInfo(message, module, service, cause);
        break;
      case Level::Notice:
        logNotice(message, module, service, cause);
        break;
      case Level::Warning:
        logWarning(message, module, service, cause);
        break;
      case Level::Error:
        logError(message, module, service, cause);
        break;
      case Level::Critical:
        logCritical(message, module, service, cause);
        break;
      case Level::Fatal:
        logFatal(message, module, service, cause);
        break;
      default:
        break;
    }
  }

  inline
  void
  StdLogger::logError(const Level& level,
                      const std::string& message,
                      const std::string& cause,
                      const std::string& module,
                      const std::string& service) const noexcept
  {
    logMessage(level, message, module, service, cause);
  }

  inline
  void
  StdLogger::logFatal(const std::string& message,
                      const std::string& module,
                      const std::string& service,
                      const std::string& cause) const noexcept
  {
    logTrace(StreamFormatter::Color::Red, Level::Fatal, message, module, service, cause);
  }

  inline
  void
  StdLogger::logCritical(const std::string& message,
                         const std::string& module,
                         const std::string& service,
                         const std::string& cause) const noexcept
  {
    logTrace(StreamFormatter::Color::Red, Level::Critical, message, module, service, cause);
  }

  inline
  void
  StdLogger::logError(const std::string& message,
                      const std::string& module,
                      const std::string& service,
                      const std::string& cause) const noexcept
  {
    logTrace(StreamFormatter::Color::Red, Level::Error, message, module, service, cause);
  }

  inline
  void
  StdLogger::logWarning(const std::string& message,
                        const std::string& module,
                        const std::string& service,
                        const std::string& cause) const noexcept
  {
    logTrace(StreamFormatter::Color::Yellow, Level::Warning, message, module, service, cause);
  }

  inline
  void
  StdLogger::logNotice(const std::string& message,
                       const std::string& module,
                       const std::string& service,
                       const std::string& cause) const noexcept
  {
    logTrace(StreamFormatter::Color::Cyan, Level::Notice, message, module, service, cause);
  }

  inline
  void
  StdLogger::logInfo(const std::string& message,
                     const std::string& module,
                     const std::string& service,
                     const std::string& cause) const noexcept
  {
    logTrace(StreamFormatter::Color::Green, Level::Info, message, module, service, cause);
  }

  inline
  void
  StdLogger::logDebug(const std::string& message,
                      const std::string& module,
                      const std::string& service,
                      const std::string& cause) const noexcept
  {
    logTrace(StreamFormatter::Color::Blue, Level::Debug, message, module, service, cause);
  }

  inline
  void
  StdLogger::logVerbose(const std::string& message,
                        const std::string& module,
                        const std::string& service,
                        const std::string& cause) const noexcept
  {
    logTrace(StreamFormatter::Color::Gray, Level::Verbose, message, module, service, cause);
  }

  inline
  bool
  StdLogger::canBeDisplayed(const Level& messageLevel) const noexcept {
    return m_level <= messageLevel;
  }

  inline
  std::string
  StdLogger::getTimestamp() const noexcept {
    // Retrieve the date and time for this log.
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);

    std::ostringstream localTimeAsStringStream;
    localTimeAsStringStream << std::put_time(localTime, "%d-%m-%Y %H:%M:%S");

    return localTimeAsStringStream.str();
  }

}

#endif    /* STD_LOGGER_HXX */
