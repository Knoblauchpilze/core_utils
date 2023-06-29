
#pragma once

#include "CoreObject.hh"
#include "JobPriority.hh"
#include <memory>

namespace utils {

class AsynchronousJob : public CoreObject {
public:
  /// @brief - Interface method allowing to schedule the operations related to
  /// this object. Used by the thread pool to execute this job.
  virtual void compute() = 0;

  /// @brief - Retrieve the priority associated to this job. We assume that the
  /// priority cannot be modified once the job has been created hence the fact
  /// that we are allowed to access it without locking anything.
  /// @return - the priority associated to this job.
  auto getPriority() const noexcept -> Priority;

protected:
  /// @brief - Creates a new job with the specified priority. The default
  /// priority is set to normal. This constructor is only accessible to
  /// inheriting classes so as to provide some sort of security for who can
  /// create a new job.
  ///@param name - the name of this job.Used to provide decent logging.
  /// @param priority - the priority of the job to create.
  AsynchronousJob(const std::string &name,
                  const Priority &priority = Priority::Normal);

private:
  /// @brief - The priority associated to this job.
  Priority m_priority;
};

using AsynchronousJobShPtr = std::shared_ptr<AsynchronousJob>;
} // namespace utils

#include "AsynchronousJob.hxx"
