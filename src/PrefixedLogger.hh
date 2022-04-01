#ifndef    PREFIXED_LOGGER_HH
# define   PREFIXED_LOGGER_HH

# include <string>
# include "Logger.hh"

namespace utils {

  class PrefixedLogger: public Logger {
    public:

      /**
       * @brief - Create a wrapper around the specified logger with
       *          the specified module and service.
       * @param service - the name of the service for this logger.
       * @param module - the name of the module for this logger.
       */
      PrefixedLogger(const std::string& service,
                     const std::string& module);

      ~PrefixedLogger() = default;

      /**
       * @brief - Defines a new module for this logger.
       * @param module - the new module.
       */
      void
      setModule(const std::string& module) noexcept;

      /**
       * @brief - Defines a new service for this logger.
       * @param service - the new service.
       */
      void
      setService(const std::string& service) noexcept;

      /**
       * @brief - Implementation of the interface method. Uses the
       *          internal logger to assign the new log level.
       * @param level - the log severity to assign.
       */
      void
      setLevel(const Level& level) noexcept override;

      /**
       * @brief - Implementation of the interface method to log a
       *          message. The module and service will be added to
       *          the provided arguments.
       * @param level - the serverity of the message.
       * @param message - the content of the log.
       * @param module - a string representing the module producing
       *                 the message. Will be prefixed by the module
       *                 defined for this logger.
       * @param service - the service attached to the logger. The
       *                  internal service will be added.
       * @param cause - optional cause of the message.
       */
      void
      logMessage(const Level& level,
                 const std::string& message,
                 const std::string& module = std::string(),
                 const std::string& service = std::string(),
                 const std::string& cause = std::string()) const noexcept override;

      /**
       * @brief - Implementation of the interface method to handle the
       *          log of an error message. This requires a cause.
       * @param level - the severity of the error.
       * @param message - the text of the error.
       * @param cause - the cause of the error.
       * @param module - optional argument for the module that produced
       *                 the error.
       * @param service - optional argument for the service that produced
       *                  the error.4
       */
      void
      logError(const Level& level,
               const std::string& message,
               const std::string& cause,
               const std::string& module = std::string(),
               const std::string& service = std::string()) const noexcept override;

    private:

      /**
       * @brief - The service attached to this logger.
       */
      std::string m_service;

      /**
       * @brief - The module attached to this logger.
       */
      std::string m_module;
  };

}

#endif    /* PREFIXED_LOGGER_HH */
