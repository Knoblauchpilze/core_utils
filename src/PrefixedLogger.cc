
# include "PrefixedLogger.hh"
# include "LoggerLocator.hh"

namespace utils {

  std::string
  consolidate(const std::string& str) noexcept {
    if (str.empty() || str[0] == '[') {
      return str;
    }

    return "[" + str + "]";
  }

  PrefixedLogger::PrefixedLogger(const std::string& service,
                                 const std::string& module):
    Logger(),

    m_service(consolidate(service)),
    m_module(consolidate(module))
  {}

  void
  PrefixedLogger::setModule(const std::string& module) noexcept {
    // Surround the module by brackets.
    m_module = consolidate(module);
  }

  void
  PrefixedLogger::addModule(const std::string& module) noexcept {
    m_module += consolidate(module);
  }

  void
  PrefixedLogger::setService(const std::string& service) noexcept {
    // Surround the service by brackets.
    m_service = consolidate(service);
  }

  void
  PrefixedLogger::addService(const std::string& service) noexcept {
    m_service += consolidate(service);
  }

  void
  PrefixedLogger::setLevel(const Level& level) noexcept {
    LoggerLocator::getLogger().setLevel(level);
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

    LoggerLocator::getLogger().logMessage(level, message, mod, ser, cause);
  }

  void
  PrefixedLogger::logError(const Level& level,
                           const std::string& message,
                           const std::string& cause,
                           const std::string& module,
                           const std::string& service) const noexcept
  {
    LoggerLocator::getLogger().logMessage(level, message, module, service, cause);
  }

}
