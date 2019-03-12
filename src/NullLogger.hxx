#ifndef    NULL_LOGGER_HXX
# define   NULL_LOGGER_HXX

# include "NullLogger.hh"

namespace utils {

  inline
  void
  NullLogger::setLevel(const Level& /*level*/) noexcept {
    // Empty implementation.
  }

  inline
  void
  NullLogger::logMessage(const Level& /*level*/,
                          const std::string& /*message*/,
                          const std::string& /*module*/,
                          const std::string& /*service*/,
                          const std::string& /*cause*/) const noexcept
  {
    // Empty implementation.
  }

}

#endif    /* NULL_LOGGER_HXX */
