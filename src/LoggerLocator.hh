
#pragma once

#include "Logger.hh"
#include "NullLogger.hh"
#include <string>

namespace utils {

class LoggerLocator {
public:
  static void initialize();

  static Logger &getLogger();

  static void provide(Logger *logger);

private:
  static Logger *m_logger;
  static NullLogger sk_nullLogger;
};

} // namespace utils

#include "LoggerLocator.hxx"
