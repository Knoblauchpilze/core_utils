
# include "LoggerLocator.hh"

namespace utils {

  Logger* LoggerLocator::m_logger = nullptr;
  NullLogger LoggerLocator::sk_nullLogger;

}
