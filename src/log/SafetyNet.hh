
#pragma once

#include "PrefixedLogger.hh"
#include <functional>
#include <string>

namespace utils {

bool launchProtected(std::function<void(void)> func,
                     const std::string &functionName,
                     const std::string &module,
                     const std::string &service);

bool launchProtected(std::function<void(void)> func,
                     const std::string &functionName,
                     const log::PrefixedLogger &logger);

} // namespace utils
