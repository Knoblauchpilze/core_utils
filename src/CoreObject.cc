
# include "CoreObject.hh"

namespace utils {

  CoreObject::CoreObject(const std::string& name):
    m_name(name),
    m_service()
  {}

  CoreObject::~CoreObject() {}

}

