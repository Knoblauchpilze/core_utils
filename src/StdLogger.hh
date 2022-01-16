#ifndef    STD_LOGGER_HH
# define   STD_LOGGER_HH

# include <mutex>
# include <string>

# include "Logger.hh"
# include "StreamFormatter.hh"

namespace utils {

  class StdLogger : public Logger {
    public:

      StdLogger();

      ~StdLogger() = default;

      void
      setLevel(const Level& level) noexcept override;

      void
      logMessage(const Level& level,
                 const std::string& message,
                 const std::string& module,
                 const std::string& service,
                 const std::string& cause) const noexcept override;

      void
      logError(const Level& level,
               const std::string& message,
               const std::string& cause,
               const std::string& module,
               const std::string& service) const noexcept override;

    private:

      void
      logFatal(const std::string& message,
               const std::string& module,
               const std::string& service,
               const std::string& cause) const noexcept;

      void
      logCritical(const std::string& message,
                  const std::string& module,
                  const std::string& service,
                  const std::string& cause) const noexcept;

      void
      logError(const std::string& message,
               const std::string& module,
               const std::string& service,
               const std::string& cause) const noexcept;

      void
      logWarning(const std::string& message,
                 const std::string& module,
                 const std::string& service,
                 const std::string& cause) const noexcept;

      void
      logNotice(const std::string& message,
                const std::string& module,
                const std::string& service,
                const std::string& cause) const noexcept;

      void
      logInfo(const std::string& message,
              const std::string& module,
              const std::string& service,
              const std::string& cause) const noexcept;

      void
      logDebug(const std::string& message,
               const std::string& module,
               const std::string& service,
               const std::string& cause) const noexcept;

      void
      logVerbose(const std::string& message,
                 const std::string& module,
                 const std::string& service,
                 const std::string& cause) const noexcept;

      bool
      canBeDisplayed(const Level& messageLevel) const noexcept;

      std::string
      getTimestamp() const noexcept;

      void
      logTrace(const StreamFormatter::Color& color,
               const Level& level,
               const std::string& message,
               const std::string& module,
               const std::string& service,
               const std::string& cause) const noexcept;

    private:

      mutable std::mutex m_locker;
      bool m_enableLog;
      Level m_level;
      StreamFormatter m_formatter;
  };

}

# include "StdLogger.hxx"

#endif    /* STD_LOGGER_HH */
