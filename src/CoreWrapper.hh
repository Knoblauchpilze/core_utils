#ifndef    CORE_WRAPPER_HH
# define   CORE_WRAPPER_HH

# include <string>
# include <functional>

namespace core {
  namespace utils {

    void
    launchProtected(std::function<void(void)> func,
                    const std::string& functionName,
                    const std::string& module);

  }
}

# include "CoreWrapper.hxx"

#endif    /* CORE_WRAPPER_HH */
