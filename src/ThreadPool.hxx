#ifndef    THREAD_POOL_HXX
# define   THREAD_POOL_HXX

# include "ThreadPool.hh"

namespace utils {

  inline
  ThreadPool::~ThreadPool() {
    terminateThreads();
  }

  inline
  unsigned
  ThreadPool::getThreadPoolSize() noexcept {
    return 3u;
  }

  inline
  bool
  ThreadPool::hasJobs() const noexcept {
    return !m_hPrioJobs.empty() || !m_nPrioJobs.empty() || !m_lPrioJobs.empty();
  }

}

#endif    /* THREAD_POOL_HXX */
