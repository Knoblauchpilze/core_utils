#ifndef    CORE_WRAPPER_HXX
# define   CORE_WRAPPER_HXX

# include "CoreWrapper.hh"

# include "LoggerLocator.hh"
# include "CoreException.hh"

namespace utils {

  inline
  void
  launchProtected(std::function<void(void)> func,
                  const std::string& functionName,
                  const std::string& module,
                  const std::string& service)
  {
    try {
      func();
    }
    catch (const CoreException& e) {
      LoggerLocator::getLogger().logMessage(
        Level::Error,
        std::string("Caught exception while executing \"") + functionName + "\"",
        module,
        service,
        e.what()
      );
    }
    catch (const std::exception& e) {
      LoggerLocator::getLogger().logMessage(
        Level::Error,
        std::string("Caught unexpected exception while executing \"") + functionName + "\"",
        module,
        service,
        e.what()
      );
    }
    catch (...) {
      LoggerLocator::getLogger().logMessage(
        Level::Error,
        std::string("Unknown error while executing \"") + functionName + "\"",
        module,
        service
      );
    }
  }

}

#endif    /* CORE_WRAPPER_HXX */
