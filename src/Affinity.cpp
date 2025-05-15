#include "Affinity.hpp"

std::atomic<bool> affinityEnabled(false);

#if defined(__APPLE__)
  #include <pthread.h>
  #include <mach/thread_act.h>
  #include <mach/thread_policy.h>
  #include <mach/mach_init.h>

  void bindThreadToCore(std::size_t core) {
      thread_port_t machThread = pthread_mach_thread_np(pthread_self());
      thread_affinity_policy_data_t policy = { static_cast<integer_t>(core) };
      // count = 1
      (void)thread_policy_set(
          machThread,
          THREAD_AFFINITY_POLICY,
          reinterpret_cast<thread_policy_t>(&policy),
          1
      );
  }

#elif defined(__linux__)
  #include <pthread.h>
  #include <sched.h>

  void bindThreadToCore(std::size_t core) {
      cpu_set_t cpuset;
      CPU_ZERO(&cpuset);
      CPU_SET(core, &cpuset);
      pthread_setaffinity_np(pthread_self(),
                             sizeof(cpuset),
                             &cpuset);
  }

#else
  void bindThreadToCore(std::size_t) {
      // No-op on other platforms
  }
#endif
