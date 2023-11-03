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
  CoreObject::allowLog(bool logging) {
    m_allowLog = logging;
  }

  inline
  void
  CoreObject::setName(const std::string& name) noexcept {
    m_log.setModule(name);
    m_name = name;
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
    if (m_allowLog) {
      m_log.logMessage(level, message, "", "");
    }
  }

  inline
  void
  CoreObject::info(const std::string& message) const noexcept {
    if (m_allowLog) {
      m_log.logMessage(utils::Level::Info, message, "", "", "");
    }
  }

  inline
  void
  CoreObject::warn(const std::string& message,
                   const std::string& cause) const
  {
    if (m_allowLog) {
      m_log.logMessage(utils::Level::Warning, message, "", "", cause);
    }
  }

  inline
  void
  CoreObject::error(const std::string& message,
                    const std::string& cause) const
  {
    throw CoreException(
      message,
      m_log.getModule(),
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
      m_log.getModule(),
      m_service,
      cause
    );
  }

}

#endif    /* CORE_OBJECT_HXX */
