#ifndef    SIGNAL_HH
# define   SIGNAL_HH

# include <map>
# include <mutex>
# include <functional>

namespace utils {

  template <typename... Args>
  class Signal {
    public:

      using Receiver = std::function<void(Args...)>;

    public:

      /**
       * @brief - Creates a default signal with no listeners.
       */
      Signal();

      /**
       * @brief - Registers the method `func` of the instance `inst` as
       *          listener of this signal.
       * @param inst - the instance of the class of type `T` to connect.
       * @param func - the method of the instance to connect.
       * @return - an identifier of the connnected slot, which can be used
       *           to disconnect the object.
       */
      template <typename T>
      int
      connect_member(T* inst,
                     void (T::*func)(Args...));

      /**
       * @brief - Registers the method `func` of the instance `inst` as
       *          listener of this signal.
       * @param inst - the instance of the class of type `T` to connect.
       * @param func - the method of the instance to connect.
       * @return - an identifier of the connected slot, which can be used
       *           to disconnect the object.
       */
      template <typename T>
      int
      connect_member(T* inst,
                     void (T::*func)(Args...) const);

      /**
       * @brief - Connects the free function `slot` to this signal so that
       *          it is notified whenever this signal is fired.
       * @param slot - the function to connect.
       * @return - an identifier which can be used to disconnect the function
       *           from this signal if needed.
       */
      int
      connect(const Receiver& slot) const;

      /**
       * @brief - Disconnects the slot reppresented by the identifier `id`. If
       *          no such signal exists nothing happens.
       */
      void
      disconnect(int id) const;

      /**
       * @brief - Disconnects all the slots registered in this signal.
       */
      void
      disconnectAll() const;

      /**
       * @brief - Emits the signal to all the listeners forwarding the arguments `p`.
       * @param p - a list of arguments to forward to listeners.
       */
      void
      emit(Args... p);

    private:

      using ReceiversMap = std::unordered_map<int, Receiver>;

      /**
       * @brief - Describes the id to assign to the next listener to register on this signal.
       */
      mutable int m_listenerID;

      /**
       * @brief - Describes all the slot to call whenever this signal is emitted.
       */
      mutable ReceiversMap m_slots;

      /**
       * @brief - Protects concurrent access to this signal.
       */
      mutable std::mutex m_locker;
  };

}

# include "Signal.hxx"

#endif    /* SIGNAL_HH */
