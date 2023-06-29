
#pragma once

#include "AsynchronousJob.hh"

namespace utils {

inline AsynchronousJob::AsynchronousJob(const std::string &name,
                                        const Priority &priority)
    : CoreObject(name),

      m_priority(priority) {
  setService("job");
}

inline auto AsynchronousJob::getPriority() const noexcept -> Priority {
  return m_priority;
}

} // namespace utils
