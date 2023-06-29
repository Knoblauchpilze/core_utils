
#pragma once

#include "Chrono.hh"

namespace utils {

template <class Duration>
inline Chrono<Duration>::Chrono(const std::string &message,
                                const std::string &name, const Level &severity)
    : CoreObject(name), m_scopes(), m_severity(severity) {
  setService(std::string("chrono"));
  addScope(message);
}

template <class Duration> inline Chrono<Duration>::~Chrono() {
  // Print all remaining scopes upon exiting the logger.
  while (!m_scopes.empty()) {
    // Print the current scope.
    finish();
  }
}

template <class Duration>
inline void Chrono<Duration>::addScope(const std::string &message) {
  m_scopes.push(std::make_pair(message, std::chrono::steady_clock::now()));
}

template <class Duration> inline void Chrono<Duration>::finish() {
  // Retrieve the scope containing information about the starting date.
  if (m_scopes.empty()) {
    error(std::string("Cannot display elapsed duration, no available scope"));
  }

  TimeScope scope = m_scopes.top();
  finalize(scope);
  m_scopes.pop();
}

template <class Duration>
inline void Chrono<Duration>::finalize(const TimeScope &scope) {
  // Compute the duration of this scope.
  Timestamp now = std::chrono::steady_clock::now();
  int duration =
      std::chrono::duration_cast<Duration>(now - scope.second).count();

  // Log the message.
  log(scope.first + " took " + std::to_string(duration) + " " +
          std::to_string(Duration::period::num) + "/" +
          std::to_string(Duration::period::den) + "s",
      m_severity);
}

// Template specialization in case of common time durations.
template <>
inline void
Chrono<std::chrono::milliseconds>::finalize(const TimeScope &scope) {
  // Compute the duration of this scope.
  Timestamp now = std::chrono::steady_clock::now();
  int duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(now - scope.second)
          .count();

  // Log the message.
  log(scope.first + " took " + std::to_string(duration) + "ms", m_severity);
}

template <>
inline void Chrono<std::chrono::seconds>::finalize(const TimeScope &scope) {
  // Compute the duration of this scope.
  Timestamp now = std::chrono::steady_clock::now();
  int duration =
      std::chrono::duration_cast<std::chrono::seconds>(now - scope.second)
          .count();

  // Log the message.
  log(scope.first + " took " + std::to_string(duration) + "s", m_severity);
}

template <>
inline void
Chrono<std::chrono::microseconds>::finalize(const TimeScope &scope) {
  // Compute the duration of this scope.
  Timestamp now = std::chrono::steady_clock::now();
  int duration =
      std::chrono::duration_cast<std::chrono::microseconds>(now - scope.second)
          .count();

  // Log the message.
  log(scope.first + " took " + std::to_string(duration) + "mics", m_severity);
}

} // namespace utils
