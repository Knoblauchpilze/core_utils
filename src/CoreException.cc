
# include "CoreException.hh"

# include <vector>
# include <execinfo.h>

# include "CoreLogger.hh"

namespace core {
  namespace utils {

    const unsigned CoreException::sk_stackTraceDepth = 32u;

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
    CoreException::logError(const Level& level) const
    {
      core::utils::Logger::getInstance().logMessage(
        level,
        getMessage(),
        getModule(),
        getCause()
      );
    }

  }
}