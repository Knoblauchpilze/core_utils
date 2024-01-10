
#pragma once

#include "AsynchronousJob.hh"
#include "CoreObject.hh"
#include "Signal.hh"
#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

namespace utils {

class ThreadPool : public CoreObject
{
  public:
  /// @brief - Create a new thread pool with the specified thread count. It allows
  /// to schedule the execution of jobs through the provided interface. Note that
  /// in case the provided value is `0` the value returned by `getThreadPoolSize`
  /// will be used instead.
  /// @param size - the number of threads to create for this pool.
  ThreadPool(const unsigned size = 3u);

  /// @brief - Used to destroy the pool and terminate all the threads used to process
  /// the jobs. The jobs will be finished before destroying the threads.
  virtual ~ThreadPool();

  /// @brief - Used to notify that some jobs have been inserted into the internal
  /// queue and that threads can start the computation.
  void notifyJobs();

  /// @brief - Used to enqueue the list of jobs provided in input into the internal
  /// queue. The user should call the `notifyJobs` method to actually start the
  /// processing.
  /// One can choose whether these jobs invalidate the work that is being processes
  /// right now or on the other hand if it does not impact it. The second boolean,
  /// if set to `true` will prevent the notification of  jobs from previous batches
  /// through the `onJobsCompleted` signal. If the value is set to `false`, the user
  /// will still be able to get some notifications about previously submitted jobs.
  /// @param jobs - the list of jobs to enqueue.
  /// @param invalidate - prevent notification of jobs from previous batches if set
  /// to `true`.
  void enqueueJobs(const std::vector<AsynchronousJobShPtr> &jobs, const bool invalidate);

  /// @brief - Used to cancel any existing jobs being processed for this scheduler.
  /// This function is needed in order to be able to call `enqueueJobs` again.
  void cancelJobs();

  private:
  /// @brief - Used to create the thread pool used by this scheduler to perform the user's
  /// computations. The threads are created while building this scheduler and are waiting
  /// for jobs to be enqueued. The number of threads to create is retrieved from the input
  /// argument.
  /// @param size - the number of thread(s) to create for this pool.
  void createThreadPool(const unsigned size);

  /// @brief - Used to terminate the threads associated to the thread pool. This is typically
  /// called upon destroying the scheduler.
  void terminateThreads();

  /// @brief - Used as a thread loop method when creating the pool. This method will be executed
  /// by each individual thread and handles the querying of the jobs, processing itself,
  /// notification of the results and termination when needed.
  /// This method takes an identifier that is used to identify the jobs processed by the thread.
  /// @param threadId - a provided counter identifying this thread. Nothing fancy but it allows
  /// to easily determine from which thread the completed jobs come from.
  void jobFetchingLoop(const unsigned threadId);

  /// @brief - Used as a thread loop method when creating the pool to handle the results produced
  /// by the threads and notify it somehow to external listeners. The results are analyzed to determine
  /// whether they belong to the batch currently being processed: in any other case they are discarded.
  void resultsHandlingLoop();

  /**
       * @brief - Used to determine whether any jobs at all are registered. Scans all the priority queues
       *          and return `true` if at least one of them is not empty. Assumes that the locker used to
       *          protect the jobs' queues is already acquired.
       * @return - `true` if at least one job is subtmitted (no matter the priority).
       */
  bool hasJobs() const noexcept;

  private:
  /**
       * @brief - Convenience define to refer to a unique lock on the mutex used to
       *          protect the pool's running status.
       */
  using UniqueGuard = std::unique_lock<std::mutex>;

  /// @brief - Convenience structure representing a job and the corresponding batch
  /// index. This allows to identify whether a result is linked to the current
  /// batch or to an old one.
  struct Job
  {
    AsynchronousJobShPtr task{};
    unsigned batch{0u};
  };

  /// @brief - A mutex protecting concurrent accesses to the threads composing the
  /// pool. Typically used to start or stop the thread pool.
  std::mutex m_poolLocker{};

  /// @brief - Condition variable used to put threads of the pool to sleep as long
  /// as no jobs are provided and the pool does not need to be terminated.
  std::condition_variable m_waiter{};

  /// @brief - Keep track of whether the pool is running. As long as this value is
  /// `true` individual threads can continue fetching information and wait for jobs.
  bool m_poolRunning{false};

  /// @brief - Indicates whether there are some jobs to process. A `true` value
  /// tells that the internal queue for computing jobs has at least one value. We
  /// protect this boolean behind the same locker (i.e. the `m_poolLocker` one) as
  /// the `m_poolRunning` boolean because we want threads to be notified either
  /// when the pool needs to be terminated or when some new jobs are available.
  bool m_jobsAvailable{false};

  /// @brief - Protect concurrent accesses to the array of threads.
  std::mutex m_threadsLocker{};

  /// @brief - The threads used by the pool. When the pool is up and running there
  /// should be the configured amount of threads registered in the vector. A
  /// termination of the pool destroys the thread but in general they should not be
  /// accessed directly.
  std::vector<std::thread> m_threads{};

  /// @brief - Protect concurrent accesses to the jobs queue and related properties.
  std::mutex m_jobsLocker{};

  /// @brief - The list of jobs currently available for processing. Contains all the
  /// high priority jobs.
  std::vector<Job> m_hPrioJobs{};

  /// @brief - Similar to the `m_hPrioJobs` queue but contains normal priority jobs.
  std::vector<Job> m_nPrioJobs{};

  /// @brief - Similar to the `m_hPrioJobs` queue but contains the low priority jobs.
  std::vector<Job> m_lPrioJobs{};

  /// @brief - An index identifying the current batch of jobs being fed to the
  /// threads. Any completion related to another batch will be discarded as it's
  /// probably irrelevant anymore.
  unsigned m_batchIndex{0u};

  /// @brief - Protects the access to the results properties (thread and waiting condition).
  std::mutex m_resultsLocker{};

  /// @brief - Indicates whether the results handling process should still be occuring.
  /// This allows to terminate gracefully the results thread.
  bool m_resultsHandling{false};

  /// @brief - The list of jobs already computed, available for analysis.
  std::vector<Job> m_results{};

  /// @brief - Defines whether the job related to an old batch should be considered valid
  /// or if no notification should be produced for them.
  bool m_invalidateOld{true};

  /// @brief - Waiting condition to communicate results to the dedicated thread.
  std::condition_variable m_resWaiter{};

  /// @brief - A mutex protecting the results handling thread.
  std::mutex m_resultsThreadLocker{};

  ///@brief - A thread used to handle the results communicated by other threads of the
  /// pool. This one should be terminated after all the other threads otherwise we could
  /// hang the program.
  std::thread m_resultsHandlingThread{};

  public:
  /// @brief - This signal is emitted by the scheduler as soon as some jobs have been
  /// successfully rendered by the thread pool.
  /// Any listener whishing to update itself with the results of the process can
  /// register on this signal and be notified when that happens.
  Signal<const std::vector<AsynchronousJobShPtr> &> onJobsCompleted{};
};

using ThreadPoolShPtr = std::shared_ptr<ThreadPool>;

} // namespace utils
