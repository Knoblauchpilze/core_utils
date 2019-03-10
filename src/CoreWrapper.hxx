#ifndef    CORE_WRAPPER_HXX
# define   CORE_WRAPPER_HXX

# include "CoreWrapper.hh"

# include "CoreLogger.hh"
# include "CoreException.hh"

namespace core {
  namespace utils {

    inline
    void
    launchProtected(std::function<void(void)> func,
                    const std::string& functionName,
                    const std::string& module)
    {
      try {
        func();
      }
      catch (const CoreException& e) {
        Logger::getInstance().logError(
          std::string("Caught exception while executing \"") + functionName + "\"",
          module,
          e.what()
        );
      }
      catch (const std::exception& e) {
        Logger::getInstance().logError(
          std::string("Caught unexpected exception while executing \"") + functionName + "\"",
          module,
          e.what()
        );
      }
      catch (...) {
        Logger::getInstance().logError(
          std::string("Unknown error while executing \"") + functionName + "\"",
          module
        );
      }
    }

  }
}

#endif    /* CORE_WRAPPER_HXX */
