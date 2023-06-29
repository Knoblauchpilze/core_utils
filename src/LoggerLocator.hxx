
#pragma once

#include "LoggerLocator.hh"

namespace utils {

inline void LoggerLocator::initialize() { m_logger = &sk_nullLogger; }

inline Logger &LoggerLocator::getLogger() { return *m_logger; }

inline void LoggerLocator::provide(Logger *logger) {
  if (logger == nullptr) {
    // Revert to null service.
    m_logger = &sk_nullLogger;
  } else {
    m_logger = logger;
  }
}

} // namespace utils
