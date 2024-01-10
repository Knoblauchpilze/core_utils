
#pragma once

#include "Chrono.hh"

namespace utils {

template<class Duration>
inline Chrono<Duration>::Chrono(const std::string &message)
  : Chrono<Duration>(message, "unnamed chrono")
{}

template<class Duration>
inline Chrono<Duration>::Chrono(const std::string &message, const std::string &name)
  : CoreObject(name)
{
  setService("chrono");
  addScope(message);
}

template<class Duration>
inline Chrono<Duration>::~Chrono()
{
  while (!m_scopes.empty())
  {
    finish();
  }
}

template<class Duration>
inline void Chrono<Duration>::addScope(const std::string &message)
{
  m_scopes.push(std::make_pair(message, std::chrono::steady_clock::now()));
}

template<class Duration>
inline void Chrono<Duration>::finish()
{
  if (m_scopes.empty())
  {
    error("Cannot display elapsed duration", "No available scope");
  }

  TimeScope scope = m_scopes.top();
  finalize(scope);
  m_scopes.pop();
}

template<class Duration>
inline void Chrono<Duration>::finalize(const TimeScope &scope)
{
  Timestamp now = std::chrono::steady_clock::now();
  int duration  = std::chrono::duration_cast<Duration>(now - scope.second).count();

  debug(scope.first + " took " + std::to_string(duration) + " "
        + std::to_string(Duration::period::num) + "/" + std::to_string(Duration::period::den) + "s");
}

// Template specialization in case of common time durations.
template<>
inline void Chrono<std::chrono::milliseconds>::finalize(const TimeScope &scope)
{
  Timestamp now = std::chrono::steady_clock::now();
  int duration  = std::chrono::duration_cast<std::chrono::milliseconds>(now - scope.second).count();

  debug(scope.first + " took " + std::to_string(duration) + "ms");
}

template<>
inline void Chrono<std::chrono::seconds>::finalize(const TimeScope &scope)
{
  Timestamp now = std::chrono::steady_clock::now();
  int duration  = std::chrono::duration_cast<std::chrono::seconds>(now - scope.second).count();

  debug(scope.first + " took " + std::to_string(duration) + "s");
}

template<>
inline void Chrono<std::chrono::microseconds>::finalize(const TimeScope &scope)
{
  Timestamp now = std::chrono::steady_clock::now();
  int duration  = std::chrono::duration_cast<std::chrono::microseconds>(now - scope.second).count();

  debug(scope.first + " took " + std::to_string(duration) + "mics");
}

} // namespace utils
