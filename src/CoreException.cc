
# include "CoreException.hh"

# include <vector>
# include <execinfo.h>
# include "LoggerLocator.hh"

namespace utils {

  const unsigned CoreException::sk_stackTraceDepth = 32u;

  CoreException::CoreException(const std::string& message,
                               const std::string& module,
                               const std::string& service,
                               const CoreException& cause,
                               const Level& level):
    std::exception(),
    m_message(message),
    m_module(module),
    m_service(service),
    m_cause(cause.what())
  {
    // Assign a module if needed.
    if (m_module.empty()) {
      m_module = cause.getModule();
    }

    // Assign a service if needed.
    if (m_service.empty()) {
      m_service = cause.getService();
    }

    // Perform the logging of this error.
    logError(level);
  }

  std::string
  CoreException::getFormattedMessage() const noexcept {
    std::string serviceString;
    if (hasService()) {
      serviceString = std::string("[") + getService() + "] ";
    }

    std::string moduleString;
    if (hasModule()) {
      moduleString = std::string("[") + getModule() + "] ";
    }

    std::string causeString;
    if (hasCause()) {
      causeString = std::string(" (cause: \"") + getCause() + "\")";
    }

    return serviceString + moduleString + m_message + causeString;
  }

  std::string
  CoreException::retrieveStackTrace() const noexcept {
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

  void
  CoreException::logError(const Level& level) const {
    LoggerLocator::getLogger().logMessage(
      level,
      getMessage(),
      getModule(),
      getService(),
      getCause()
    );
  }

}