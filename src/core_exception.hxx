#ifndef    CORE_EXCEPTION_HXX_
# define   CORE_EXCEPTION_HXX_

# include "core_exception.hh"

namespace core {

  inline
  const char*
  InternalException::what() const noexcept {
    return m_message.c_str();
  }

}

#endif    /*! CORE_EXCEPTION_HXX_ */
