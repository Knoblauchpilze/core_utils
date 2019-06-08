#ifndef    CORE_OBJECT_HH
# define   CORE_OBJECT_HH

# include <string>
# include <functional>
# include "LogLevel.hh"
# include "CoreException.hh"

namespace utils {

  class CoreObject {
    public:

      CoreObject(const std::string& name,
                 const bool allowLog = true);

      virtual ~CoreObject();

      const std::string&
      getName() const noexcept;

      void
      allowLog(const bool logging);

    protected:

      void
      setService(const std::string& service) noexcept;

      void
      withSafetyNet(std::function<void(void)> func,
                    const std::string& function) const;

      virtual void
      log(const std::string& message,
          const Level& level = Level::Debug) const noexcept;

      virtual void
      error(const std::string& message,
            const std::string& cause = std::string()) const;

      virtual void
      error(const std::string& message,
            const CoreException& cause) const;

    private:

      std::string m_name;
      std::string m_service;
      bool m_allowLog;
  };

}

# include "CoreObject.hxx"

#endif    /* CORE_OBJECT_HH */
