
# include "CoreObject.hh"

namespace utils {

  CoreObject::CoreObject(const std::string& name,
                         const bool allowLog):
    m_name(name),
    m_service(),
    m_allowLog(allowLog)
  {}

  CoreObject::~CoreObject() {}

}

