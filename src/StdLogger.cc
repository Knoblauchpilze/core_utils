
# include "StdLogger.hh"
# include <iostream>

namespace utils {

  StdLogger::StdLogger():
    m_locker(),
    m_enableLog(true),
    m_level(Level::Debug),
    m_formatter()
  {}

  void
  StdLogger::logTrace(const StreamFormatter::Color& color,
                      const Level& level,
                      const std::string& message,
                      const std::string& module,
                      const std::string& service,
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
    output << "[" << service << "] ";
    output << getTimestamp() << " ";

    m_formatter.setStreamColor(output, color);
    output << "[" << convertLevelToLevelString(level) << "]" << " [" << module << "] ";
    m_formatter.clearStreamFormat(output);

    output << message;

    if (!cause.empty()) {
      output << " (cause: \"" << cause << "\")";
    }

    std::cout << output.str() << std::endl;
  }

}
