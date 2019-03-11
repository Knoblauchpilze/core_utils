#ifndef    CORE_LOGGER_HXX
# define   CORE_LOGGER_HXX

# include "CoreLogger.hh"

namespace utils {
  namespace core {

    inline
    Logger&
    Logger::getInstance() {
      return s_logger;
    }

    inline
    std::string
    Logger::getName() const noexcept {
      std::lock_guard<std::mutex> lock(*m_locker);
      return m_name;
    }

    inline
    void
    Logger::setName(const std::string& name) noexcept {
      std::lock_guard<std::mutex> lock(*m_locker);
      m_name = name;
    }

    inline
    std::string
    Logger::getEnvironment() const noexcept {
      std::lock_guard<std::mutex> lock(*m_locker);
      return m_environment;
    }

    inline
    void
    Logger::setEnvironment(const std::string& environment) noexcept {
      std::lock_guard<std::mutex> lock(*m_locker);
      m_environment = environment;
    }

    inline
    void
    Logger::setLevel(const std::string& level) noexcept {
      setLevel(convertLevelStringToLevel(level));
    }

    inline
    void
    Logger::setLevel(const Level& level) noexcept {
      std::lock_guard<std::mutex> lock(*m_locker);
      m_level = level;
    }

    inline
    void
    Logger::setLoggingDevice(std::shared_ptr<LoggingDevice> device) {
      std::lock_guard<std::mutex> lock(*m_locker);
      m_loggingDevice = device;
    }

    inline
    void
    Logger::disableLog() noexcept {
      std::lock_guard<std::mutex> lock(*m_locker);
      m_enableLog = false;
    }

    inline
    void
    Logger::logFatal(const std::string& message, const std::string& module, const std::string& cause) const noexcept {
      logTrace(StreamFormatter::Color::Red, Level::Fatal, module, message, cause);
    }

    inline
    void
    Logger::logCritical(const std::string& message, const std::string& module, const std::string& cause) const noexcept {
      logTrace(StreamFormatter::Color::Red, Level::Critical, module, message, cause);
    }

    inline
    void
    Logger::logError(const std::string& message, const std::string& module, const std::string& cause) const noexcept {
      logTrace(StreamFormatter::Color::Red, Level::Error, module, message, cause);
    }

    inline
    void
    Logger::logWarning(const std::string& message, const std::string& module, const std::string& cause) const noexcept {
      logTrace(StreamFormatter::Color::Yellow, Level::Warning, module, message, cause);
    }

    inline
    void
    Logger::logNotice(const std::string& message, const std::string& module, const std::string& cause) const noexcept {
      logTrace(StreamFormatter::Color::Cyan, Level::Info, module, message, cause);
    }

    inline
    void
    Logger::logInfo(const std::string& message, const std::string& module, const std::string& cause) const noexcept {
      logTrace(StreamFormatter::Color::Green, Level::Info, module, message, cause);
    }

    inline
    void
    Logger::logDebug(const std::string& message, const std::string& module, const std::string& cause) const noexcept {
      logTrace(StreamFormatter::Color::Blue, Level::Debug, module, message, cause);
    }

    inline
    void
    Logger::logMessage(const Level& level,
                       const std::string& message,
                       const std::string& module,
                       const std::string& cause) const noexcept
    {
      switch (level) {
        case Level::Debug:
          logDebug(message, module, cause);
          break;
        case Level::Info:
          logInfo(message, module, cause);
          break;
        case Level::Notice:
          logNotice(message, module, cause);
          break;
        case Level::Warning:
          logWarning(message, module, cause);
          break;
        case Level::Error:
          logError(message, module, cause);
          break;
        case Level::Critical:
          logCritical(message, module, cause);
          break;
        case Level::Fatal:
          logFatal(message, module, cause);
          break;
        default:
          break;
      }
    }

    inline
    bool
    Logger::canBeDisplayed(const Level& messageLevel) const noexcept {
      return m_level <= messageLevel;
    }

  }
}

#endif    /* CORE_LOGGER_HXX */
