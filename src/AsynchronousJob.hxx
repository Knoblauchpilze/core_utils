#ifndef    ASYNCHRONOUS_JOB_HXX
# define   ASYNCHRONOUS_JOB_HXX

# include "AsynchronousJob.hh"

namespace utils {

  inline
  AsynchronousJob::AsynchronousJob(const std::string& name,
                                   const Priority& priority):
    CoreObject(name),

    m_priority(priority)
  {
    setService("job");
  }

  inline
  Priority
  AsynchronousJob::getPriority() const noexcept {
    return m_priority;
  }

}

#endif    /* ASYNCHRONOUS_JOB_HXX */
