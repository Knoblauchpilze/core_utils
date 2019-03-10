#ifndef    CORE_LOGGER_HH
# define   CORE_LOGGER_HH

# include <mutex>
# include <string>

# include "CoreLogLevel.hh"
# include "CoreStreamFormatter.hh"
# include "CoreLoggingDevice.hh"

namespace core {
  namespace utils {

    class Logger {
      public:

        Logger();

        ~Logger() = default;

        static
        Logger&
        getInstance();

        std::string
        getName() const noexcept;

        void
        setName(const std::string& name) noexcept;

        std::string
        getEnvironment() const noexcept;

        void
        setEnvironment(const std::string& environment) noexcept;

        void
        setLevel(const std::string& level) noexcept;

        void
        setLevel(const Level& level) noexcept;

        void
        setLoggingDevice(LoggingDeviceShPtr device);

        void
        disableLog() noexcept;

        void
        logFatal(const std::string& message,
                 const std::string& module = std::string("generic module"),
                 const std::string& cause = std::string()) const noexcept;

        void
        logCritical(const std::string& message,
                    const std::string& module = std::string("generic module"),
                    const std::string& cause = std::string()) const noexcept;

        void
        logError(const std::string& message,
                 const std::string& module = std::string("generic module"),
                 const std::string& cause = std::string()) const noexcept;

        void
        logWarning(const std::string& message,
                   const std::string& module = std::string("generic module"),
                   const std::string& cause = std::string()) const noexcept;

        void
        logNotice(const std::string& message,
                  const std::string& module = std::string("generic module"),
                  const std::string& cause = std::string()) const noexcept;

        void
        logInfo(const std::string& message,
                const std::string& module = std::string("generic module"),
                const std::string& cause = std::string()) const noexcept;

        void
        logDebug(const std::string& message,
                 const std::string& module = std::string("generic module"),
                 const std::string& cause = std::string()) const noexcept;

        void
        logMessage(const Level& level,
                   const std::string& message,
                   const std::string& module,
                   const std::string& cause) const noexcept;

      private:

        bool
        canBeDisplayed(const Level& messageLevel) const noexcept;

        std::string
        getTimestamp() const noexcept;

        void
        logTrace(const StreamFormatter::Color& color,
                 const Level& level,
                 const std::string& module,
                 const std::string& message,
                 const std::string& cause) const noexcept;

      private:

        /**
        * @brief - The static instance of this logger.
        */
        static Logger s_logger;

        mutable std::mutex m_locker;
        bool m_enableLog;
        Level m_level;
        std::string m_name;
        std::string m_environment;
        StreamFormatter m_formatter;

        LoggingDeviceShPtr m_loggingDevice;
    };

  }
}

# include "CoreLogger.hxx"

#endif    /* CORE_LOGGER_HH */
