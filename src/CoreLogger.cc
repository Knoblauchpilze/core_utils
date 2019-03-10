
# include "CoreLogger.hh"

# include <ctime>
# include <iomanip>
# include <cstring>
# include <sstream>
# include <iostream>

namespace core {
  namespace utils {

    Logger Logger::s_logger;

    Logger::Logger():
      m_locker(),
      m_enableLog(true),
      m_level(Level::Debug),
      m_name("default logger"),
      m_environment("local"),
      m_formatter(),

      m_loggingDevice(std::make_shared<LoggingDevice>())
    {}

    inline
    std::string
    Logger::getTimestamp() const noexcept {
      // Retrieve the date and time for this log.
      std::time_t currentTime = std::time(nullptr);
      std::tm* localTime = std::localtime(&currentTime);

      std::ostringstream localTimeAsStringStream;
      localTimeAsStringStream << std::put_time(localTime, "%d-%m-%Y %H:%M:%S");

      return localTimeAsStringStream.str();
    }

    void
    Logger::logTrace(const StreamFormatter::Color& color,
                     const Level& level,
                     const std::string& module,
                     const std::string& message,
                     const std::string& cause) const noexcept
    {
      // Acquire the lock on the internal mutex.
      std::lock_guard<std::mutex> lock(m_locker);

      // Check whether the message should be logged.
      if (!m_enableLog) {
        return;
      }
      if (!canBeDisplayed(level)) {
        return;
      }

      std::stringstream output;

      // Use the first color to print the application and instance name.
      m_formatter.setStreamColor(output, StreamFormatter::Color::Magenta);
      output << "[" << m_name << "] ";
      output << getTimestamp() << " ";

      m_formatter.setStreamColor(output, color);
      output << "[" << convertLevelToLevelString(level) << "]" << " [" << module << "] ";
      m_formatter.clearStreamFormat(output);

      output << message;

      if (!cause.empty()) {
        output << " (cause: \"" << cause << "\")";
      }

      output << std::endl;

      if (m_loggingDevice != nullptr) {
        m_loggingDevice->log(output.str());
      }
    }

  }
}
