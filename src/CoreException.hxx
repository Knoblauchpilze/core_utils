#ifndef    CORE_EXCEPTION_HXX
# define   CORE_EXCEPTION_HXX

# include "CoreException.hh"

namespace utils {

  inline
  CoreException::CoreException(const std::string& message,
                               const std::string& module,
                               const std::string& service,
                               const std::string& cause,
                               const Level& level):
    std::exception(),
    m_message(message),
    m_module(module),
    m_service(service),
    m_cause(cause)
  {
    // Perform the logging of this error.
    logError(level);
  }

  inline
  CoreException::CoreException(const std::string& message,
                               const std::string& module,
                               const std::string& service,
                               const CoreException& cause,
                               const Level& level):
    std::exception(),
    m_message(message),
    m_module(module),
    m_service(service),
    m_cause(cause.what())
  {
    // Assign a module if needed.
    if (m_module.empty()) {
      m_module = cause.getModule();
    }

    // Assign a service if needed.
    if (m_service.empty()) {
      m_service = cause.getService();
    }

    // Perform the logging of this error.
    logError(level);
  }

  inline
  const char*
  CoreException::what() const throw() {
    return m_cause.c_str();
  }

  inline
  std::string
  CoreException::getFormattedMessage() const noexcept {
    std::string serviceString;
    if (hasService()) {
      serviceString = std::string("[") + getService() + "] ";
    }

    std::string moduleString;
    if (hasModule()) {
      moduleString = std::string("[") + getModule() + "] ";
    }

    std::string causeString;
    if (hasCause()) {
      causeString = std::string(" (cause: \"") + getCause() + "\")";
    }

    return serviceString + moduleString + m_message + causeString;
  }

  inline
  bool
  CoreException::hasMessage() const noexcept {
    return !m_message.empty();
  }

  inline
  const std::string&
  CoreException::getMessage() const noexcept {
    return m_message;
  }

  inline
  bool
  CoreException::hasModule() const noexcept {
    return !m_module.empty();
  }

  inline
  const std::string&
  CoreException::getModule() const noexcept {
    return m_module;
  }

  inline
  bool
  CoreException::hasService() const noexcept {
    return !m_service.empty();
  }

  inline
  const std::string&
  CoreException::getService() const noexcept {
    return m_service;
  }

  inline
  bool
  CoreException::hasCause() const noexcept {
    return !m_cause.empty();
  }

  inline
  const std::string&
  CoreException::getCause() const noexcept {
    return m_cause;
  }

}

#endif    /* CORE_EXCEPTION_HXX */
