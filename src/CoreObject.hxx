#ifndef    CORE_OBJECT_HXX
# define   CORE_OBJECT_HXX

# include "CoreObject.hh"
# include "CoreWrapper.hh"
# include "LoggerLocator.hh"

namespace utils {

  inline
  const std::string&
  CoreObject::getName() const noexcept {
    return m_name;
  }

  inline
  void
  CoreObject::setService(const std::string& service) noexcept {
    m_service = service;
  }

  inline
  void
  CoreObject::withSafetyNet(std::function<void(void)> func,
                            const std::string& function) const
  {
    launchProtected(
      func,
      function,
      getName(),
      m_service
    );
  }

  inline
  void
  CoreObject::log(const std::string& message,
                  const Level& level) const noexcept
  {
    LoggerLocator::getLogger().logMessage(
      level,
      message,
      getName(),
      m_service
    );
  }

  inline
  void
  CoreObject::error(const std::string& message,
                    const std::string& cause) const
  {
    throw CoreException(
      message,
      getName(),
      m_service,
      cause
    );
  }

  inline
  void
  CoreObject::error(const std::string& message,
                    const CoreException& cause) const
  {
    throw CoreException(
      message,
      getName(),
      m_service,
      cause
    );
  }

}

#endif    /* CORE_OBJECT_HXX */
