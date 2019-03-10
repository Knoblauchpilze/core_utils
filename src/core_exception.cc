#include <execinfo.h>
#include <vector>
#include "core_exception.hh"
#include "core_logger.hh"

namespace core {

  const unsigned InternalException::sk_stackTraceDepth = 32u;

  InternalException::InternalException(const std::string&  message,
                                       const std::string&  module,
                                       const std::string&  cause,
                                       const Level&        level) noexcept:
    m_message(message)
  {
    // Log this error.
    logError(level, module, cause);
  }

  void
  InternalException::logError(const Level&  level,
                              const std::string&    module,
                              const std::string&    cause) const
  {
    std::string stackTrace = retrieveStackTrace();

    core::Logger::getInstance().logMessage(
      level,
      m_message/* + stackTrace*/,
      module,
      cause
    );
  }

  std::string
  InternalException::retrieveStackTrace() const noexcept {
    // Retrieve the stack
    std::vector<void*> array(sk_stackTraceDepth);
    size_t size;
    size = backtrace(array.data(), array.size());
    array.resize(size);

    // Convert symbols.
    char** funcs = backtrace_symbols(array.data(), array.size());

    // Build the output string.
    std::string stackTrace;
    for (unsigned stackCall = 0; stackCall < array.size(); ++stackCall) {
      stackTrace += " at ";
      stackTrace += funcs[stackCall];
      stackTrace += "\n";
    }

    return stackTrace;
  }

}
