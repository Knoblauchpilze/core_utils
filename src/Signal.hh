
#pragma once

#include <functional>
#include <map>
#include <mutex>
#include <unordered_map>

namespace utils {

template<typename... Args>
class Signal
{
  public:
  /// @brief - Convenience using to refer to a receiver function of a signal.
  using Receiver = std::function<void(Args...)>;

  Signal() = default;

  /// @brief - Registers the method `func` of the instance `inst` as listener
  /// of this signal.
  /// @param inst - the instance of the class of type `T` to connect.
  /// @param func - the method of the instance to connect.
  /// @return - an identifier of the connnected slot, which can be used to
  /// disconnect the object.
  template<typename T>
  auto connect_member(T *inst, void (T::*func)(Args...)) -> int;

  /// @brief - Registers the method `func` of the instance `inst` as listener of
  /// this signal.
  /// @param inst - the instance of the class of type `T` to connect.
  /// @param func - the method of the instance to connect.
  /// @return - an identifier of the connected slot, which can be used to disconnect
  /// the object.
  template<typename T>
  auto connect_member(T *inst, void (T::*func)(Args...) const) -> int;

  /// @brief - Connects the free function `slot` to this signal so that it is
  /// notified whenever this signal is fired.
  /// @param slot - the function to connect.
  /// @return - an identifier which can be used to disconnect the function from
  /// this signal if needed.
  auto connect(const Receiver &slot) const -> int;

  /// @brief - Disconnects the slot reppresented by the identifier `id`. If
  /// no such signal exists nothing happens.
  void disconnect(int id) const;

  /// @brief - Disconnects all the slots registered in this signal.
  void disconnectAll() const;

  /// @brief - Emits the signal to all the listeners forwarding the arguments `p`.
  /// @param p - a list of arguments to forward to listeners.
  void emit(Args... p);

  /// @brief - Emits the signal to all the listeners forwarding the arguments `p`
  /// and does so with a safety net, i.e. a way to capture exceptions.
  /// @param name - the name of the signal, used to provide nice error messages.
  /// @param p - a list of arguments to forward to listeners.
  /// @return - `true` if the execution went well and `false` otherwise.
  bool safeEmit(const std::string &name, Args... p);

  /// @brief - A convenience define to indicate that a signal identifier is
  /// not valid.
  static constexpr int NO_ID = -1;

  private:
  using ReceiversMap = std::unordered_map<int, Receiver>;

  ///@brief - Describes the id to assign to the next listener to register on
  /// this signal.
  mutable int m_listenerId{0};

  /// @brief - Describes all the slot to call whenever this signal is emitted.
  mutable ReceiversMap m_slots{};

  /// @brief - Protects concurrent access to this signal.
  mutable std::mutex m_locker{};
};

} // namespace utils

#include "Signal.hxx"
