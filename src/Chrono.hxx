#ifndef    CHRONO_HXX
# define   CHRONO_HXX

# include "Chrono.hh"

namespace utils {

  template <class Duration>
  inline
  Chrono<Duration>::Chrono(const std::string& message,
                 const std::string& name):
    CoreObject(name),
    m_scopes()
  {
    setService(std::string("chrono"));
    addScope(message);
  }

  template <class Duration>
  inline
  Chrono<Duration>::~Chrono() {
    // Print all remaining scopes upon exiting the logger.
    while (!m_scopes.empty()) {
      // Print the current scope.
      finish();
    }
  }

  template <class Duration>
  inline
  void
  Chrono<Duration>::addScope(const std::string& message) {
    m_scopes.push(
      std::make_pair(
        message,
        std::chrono::high_resolution_clock::now()
      )
    );
  }

  template <class Duration>
  inline
  void
  Chrono<Duration>::finish() {
    // Retrieve the scope containing information about the starting date.
    if (m_scopes.empty()) {
      error(std::string("Cannot display elapsed duration, no available scope"));
    }

    TimeScope scope = m_scopes.top();
    finalize(scope);
    m_scopes.pop();
  }

  template <class Duration>
  inline
  void
  Chrono<Duration>::finalize(const TimeScope& scope) {
    // Compute the duration of this scope.
    Timestamp now = std::chrono::system_clock::now();
    int duration = std::chrono::duration_cast<Duration>(now - scope.second).count();

    // Log the message.
    log(
      scope.first + " took " + std::to_string(duration) + " " +
      std::to_string(Duration::period::num) + "/" + std::to_string(Duration::period::den) +
      "s"
    );
  }

  // Template specialization in case of common time durations.
  template <>
  inline
  void
  Chrono<std::chrono::milliseconds>::finalize(const TimeScope& scope) {
    // Compute the duration of this scope.
    Timestamp now = std::chrono::system_clock::now();
    int duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - scope.second).count();

    // Log the message.
    log(scope.first + " took " + std::to_string(duration) + "ms");
  }

  template <>
  inline
  void
  Chrono<std::chrono::seconds>::finalize(const TimeScope& scope) {
    // Compute the duration of this scope.
    Timestamp now = std::chrono::system_clock::now();
    int duration = std::chrono::duration_cast<std::chrono::seconds>(now - scope.second).count();

    // Log the message.
    log(scope.first + " took " + std::to_string(duration) + "s");
  }

  template <>
  inline
  void
  Chrono<std::chrono::microseconds>::finalize(const TimeScope& scope) {
    // Compute the duration of this scope.
    Timestamp now = std::chrono::system_clock::now();
    int duration = std::chrono::duration_cast<std::chrono::microseconds>(now - scope.second).count();

    // Log the message.
    log(scope.first + " took " + std::to_string(duration) + "mics");
  }

}

#endif    /* CHRONO_HXX */
