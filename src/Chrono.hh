
#pragma once

#include "CoreObject.hh"
#include <chrono>
#include <stack>
#include <string>

namespace utils {

template <class Duration = std::chrono::milliseconds>
class Chrono : public CoreObject {
public:
  Chrono(const std::string &message,
         const std::string &name = std::string("unnamed_chrono"),
         const Level &severity = Level::Debug);

  ~Chrono();

  void addScope(const std::string &message);

  void finish();

private:
  using Timestamp = std::chrono::time_point<std::chrono::steady_clock>;
  using TimeScope = std::pair<std::string, Timestamp>;

  void finalize(const TimeScope &scope);

private:
  std::stack<TimeScope> m_scopes;

  Level m_severity;
};

/// @brief - Convenience alias for timer with known units.
using ChronoHours = Chrono<std::chrono::hours>;
using ChronoMinutes = Chrono<std::chrono::minutes>;
using ChronoSeconds = Chrono<std::chrono::seconds>;
using ChronoMilliseconds = Chrono<std::chrono::milliseconds>;
using ChronoMicroseconds = Chrono<std::chrono::microseconds>;
using ChronoNanoseconds = Chrono<std::chrono::nanoseconds>;
} // namespace utils

#include "Chrono.hxx"
