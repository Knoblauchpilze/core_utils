
#pragma once

#include "SafetyNet.hh"
#include "Signal.hh"

namespace utils {

template<typename... Args>
template<typename T>
inline auto Signal<Args...>::connect_member(T *inst, void (T::*func)(Args...)) -> int
{
  return connect([=](Args... args) { (inst->*func)(args...); });
}

template<typename... Args>
template<typename T>
inline auto Signal<Args...>::connect_member(T *inst, void (T::*func)(Args...) const) -> int
{
  return connect([=](Args... args) { (inst->*func)(args...); });
}

template<typename... Args>
inline auto Signal<Args...>::connect(const Receiver &slot) const -> int
{
  const std::lock_guard guard(m_locker);

  auto id = m_listenerId;
  ++m_listenerId;

  m_slots.insert(std::make_pair(id, slot));

  return id;
}

template<typename... Args>
inline void Signal<Args...>::disconnect(int id) const
{
  const std::lock_guard guard(m_locker);

  if (id != NO_ID)
  {
    m_slots.erase(id);
  }
}

template<typename... Args>
inline void Signal<Args...>::disconnectAll() const
{
  const std::lock_guard guard(m_locker);
  m_slots.clear();
}

template<typename... Args>
inline void Signal<Args...>::emit(Args... p)
{
  const std::lock_guard guard(m_locker);

  // Note that we cannot disconnect the signal from within this
  // call otherwise we would run into iterator invalidation
  // issues.
  for (const auto &receiver : m_slots)
  {
    receiver.second(p...);
  }
}

template<typename... Args>
inline bool Signal<Args...>::safeEmit(const std::string &name, Args... p)
{
  const std::lock_guard guard(m_locker);
  bool allGood{true};

  // Note that we cannot disconnect the signal from within this
  // call otherwise we would run into iterator invalidation
  // issues.
  for (const auto &receiver : m_slots)
  {
    if (!launchProtected([&]() { receiver.second(p...); }, name, "signal", "utils"))
    {
      allGood = false;
    }
  }

  return allGood;
}

} // namespace utils
