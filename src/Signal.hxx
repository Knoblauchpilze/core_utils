#ifndef    SIGNAL_HXX
# define   SIGNAL_HXX

# include "Signal.hh"
# include "CoreWrapper.hh"

namespace utils {

  template <typename... Args>
  inline
  Signal<Args...>::Signal():
    m_listenerID(0),
    m_slots(),
    m_locker()
  {}

  template <typename... Args>
  template <typename T>
  inline
  int
  Signal<Args...>::connect_member(T *inst, void (T::*func)(Args...)) {
    // Connect the method through a lambda.
    return connect(
      [=](Args... args) {
        (inst->*func)(args...);
      }
    );
  }

  template <typename... Args>
  template <typename T>
  inline
  int
  Signal<Args...>::connect_member(T *inst, void (T::*func)(Args...) const) {
    // Connect the method through a lambda.
    return connect(
      [=](Args... args) {
        (inst->*func)(args...);
      }
    );
  }

  template <typename... Args>
  inline
  int
  Signal<Args...>::connect(const Receiver& slot) const {
    std::lock_guard<std::mutex> guard(m_locker);

    // Select next id.
    int id = m_listenerID;
    ++m_listenerID;

    // Register in internal map.
    m_slots.insert(std::make_pair(id, slot));

    // Return the created id.
    return id;
  }

  template <typename... Args>
  inline
  void
  Signal<Args...>::disconnect(int id) const {
    std::lock_guard<std::mutex> guard(m_locker);

    // Handle error cases where the input identifier is obviously not valid.
    if (id != NoID) {
      m_slots.erase(id);
    }
  }

  template <typename... Args>
  inline
  void
  Signal<Args...>::disconnectAll() const {
    std::lock_guard<std::mutex> guard(m_locker);

    m_slots.clear();
  }

  template <typename... Args>
  inline
  void
  Signal<Args...>::emit(Args... p) {
    std::lock_guard<std::mutex> guard(m_locker);

    // Note that we cannot disconnect the signal from within this
    // call otherwise we would run into iterator invalidation
    // issues.
    for (typename ReceiversMap::iterator receiver = m_slots.begin() ;
         receiver != m_slots.cend() ;
         ++receiver)
    {
      receiver->second(p...);
    }
  }

  template <typename... Args>
  inline
  bool
  Signal<Args...>::safeEmit(const std::string& name,
                            Args... p)
  {
    std::lock_guard<std::mutex> guard(m_locker);

    bool allGood = true;

    // Note that we cannot disconnect the signal from within this
    // call otherwise we would run into iterator invalidation
    // issues.
    for (typename ReceiversMap::iterator receiver = m_slots.begin() ;
         receiver != m_slots.cend() ;
         ++receiver)
    {
      bool ret = launchProtected(
        [&]() {
          receiver->second(p...);
        },
        name,
        "signal",
        "utils"
      );

      if (!ret) {
        allGood = false;
      }
    }

    return allGood;
  }

}

# include "Signal.hxx"

#endif    /* SIGNAL_HH */
