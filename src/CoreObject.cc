
# include "CoreObject.hh"

namespace utils {

  CoreObject::CoreObject(const std::string& name,
                         bool allowLog):
    m_log("", name),

    m_name(name),
    m_service(""),
    m_allowLog(allowLog)
  {}

  CoreObject::~CoreObject() {}

  void
  CoreObject::setService(const std::string& service) noexcept {
    m_service = consolidate(service);
    m_log.setService(m_service);
  }

  void
  CoreObject::addModule(const std::string& module) noexcept {
    m_log.addModule(module);
  }

}

