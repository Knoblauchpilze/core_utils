
# include "CoreLoggingDevice.hh"

# include <iostream>

namespace utils {
  namespace core {

    void
    LoggingDevice::log(const std::string& message) const noexcept {
      std::lock_guard<std::mutex> guard(m_locker);

      std::cout << message << std::endl;
    }

  }
}
