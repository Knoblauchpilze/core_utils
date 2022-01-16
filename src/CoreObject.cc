
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

}

