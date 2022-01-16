
# include "PrefixedLogger.hh"

namespace {

  inline
  std::string
  consolidate(const std::string& str) noexcept {
    if (str.empty() || str[0] == '[') {
      return str;
    }

    return "[" + str + "]";
  }

}

namespace utils {

  PrefixedLogger::PrefixedLogger(Logger& logger,
                                 const std::string& service,
                                 const std::string& module):
    Logger(),

    m_log(logger),

    m_service(consolidate(service)),
    m_module(consolidate(module))
  {}

  void
  PrefixedLogger::setService(const std::string& service) noexcept {
    // Surround the service by brackets.
    if (service.empty()) {
      m_service = service;
    }
    else if (service[0] != '[') {
      m_service = "[" + service + "]";
    }
    else {
      m_service = service;
    }
  }

  void
  PrefixedLogger::setLevel(const Level& level) noexcept {
    m_log.setLevel(level);
  }

  void
  PrefixedLogger::logMessage(const Level& level,
                             const std::string& message,
                             const std::string& module,
                             const std::string& service,
                             const std::string& cause) const noexcept
  {
    std::string mod = m_module + consolidate(module);
    std::string ser = m_service + consolidate(service);

    m_log.logMessage(level, message, mod, ser, cause);
  }

  void
  PrefixedLogger::logError(const Level& level,
                           const std::string& message,
                           const std::string& cause,
                           const std::string& module,
                           const std::string& service) const noexcept
  {
    logMessage(level, message, module, service, cause);
  }

}
