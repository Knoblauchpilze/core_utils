#ifndef    CORE_LOGGING_DEVICE_HH
# define   CORE_LOGGING_DEVICE_HH

# include <mutex>
# include <string>
# include <memory>

namespace core {
  namespace utils {

    class LoggingDevice {
      public:

        LoggingDevice() = default;

        virtual ~LoggingDevice() = default;

        virtual void
        log(const std::string& message) const noexcept;

      private:

        mutable std::mutex m_locker;
    };

    using LoggingDeviceShPtr = std::shared_ptr<LoggingDevice>;

  }
}

#endif    /* CORE_LOGGING_DEVICE_HH */
