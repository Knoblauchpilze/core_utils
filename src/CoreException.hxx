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
  const char*
  CoreException::what() const throw() {
    return m_cause.c_str();
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
