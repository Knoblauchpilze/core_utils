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

}

#endif    /* THREAD_POOL_HXX */
