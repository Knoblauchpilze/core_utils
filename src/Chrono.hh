#ifndef    CHRONO_HH
# define   CHRONO_HH

# include <stack>
# include <string>
# include <chrono>
# include "CoreObject.hh"

namespace utils {

  template <class Duration = std::chrono::milliseconds>
  class Chrono: public CoreObject {
    public:

      Chrono(const std::string& message,
             const std::string& name = std::string("unnamed_chrono"),
             const Level& severity = Level::Debug);

      ~Chrono();

      void
      addScope(const std::string& message);

      void
      finish();

    private:

      using Timestamp = std::chrono::time_point<std::chrono::steady_clock>;
      using TimeScope = std::pair<std::string, Timestamp>;

      void
      finalize(const TimeScope& scope);

    private:

      std::stack<TimeScope> m_scopes;

      Level m_severity;
  };

}

# include "Chrono.hxx"

#endif    /* CHRONO_HH */
