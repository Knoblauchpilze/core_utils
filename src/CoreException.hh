#ifndef    CORE_EXCEPTION_HH
# define   CORE_EXCEPTION_HH

# include <stdexcept>
# include "LogLevel.hh"

namespace utils {

  class CoreException: public std::exception {
    public:

      CoreException(const std::string& message = std::string("Unexpected exception"),
                    const std::string& module = std::string(),
                    const std::string& service = std::string(),
                    const std::string& cause = std::string(),
                    const Level& level = Level::Error);

      CoreException(const std::string& message,
                    const std::string& module,
                    const std::string& service,
                    const CoreException& cause,
                    const Level& level = Level::Error);

      virtual ~CoreException() = default;

      const char*
      what() const throw() override;

      std::string
      getFormattedMessage() const noexcept;

    protected:

      bool
      hasMessage() const noexcept;

      const std::string&
      getMessage() const noexcept;

      bool
      hasModule() const noexcept;

      const std::string&
      getModule() const noexcept;

      bool
      hasService() const noexcept;

      const std::string&
      getService() const noexcept;

      const std::string&
      getCause() const noexcept;

      bool
      hasCause() const noexcept;

    private:

      std::string
      retrieveStackTrace() const noexcept;

      void
      logError(const Level& level) const;

    private:

      /**
       * @brief - The maximum stack trace level handled by this kind of exceptions.
       */
      static const unsigned sk_stackTraceDepth;

      std::string m_message;
      std::string m_module;
      std::string m_service;
      std::string m_cause;
  };

}

# include "CoreException.hxx"

#endif    /* CORE_EXCEPTION_HH */
