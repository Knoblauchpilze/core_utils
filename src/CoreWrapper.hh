#ifndef    CORE_WRAPPER_HH
# define   CORE_WRAPPER_HH

# include <string>
# include <functional>

namespace utils {

  void
  launchProtected(std::function<void(void)> func,
                  const std::string& functionName,
                  const std::string& module,
                  const std::string& service);

}

# include "CoreWrapper.hxx"

#endif    /* CORE_WRAPPER_HH */
