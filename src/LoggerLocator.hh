#ifndef    LOGGER_LOCATOR_HH
# define   LOGGER_LOCATOR_HH

# include <string>
# include "Logger.hh"
# include "NullLogger.hh"

namespace utils {

  class LoggerLocator {
    public:

      static
      void
      initialize();

      static
      Logger&
      getLogger();

      static
      void
      provide(Logger* logger);

    private:

      static Logger* m_logger;
      static NullLogger sk_nullLogger;
  };

}

# include "LoggerLocator.hxx"

#endif    /* LOGGER_LOCATOR_HH */
