#include "../include/mutex.h"
#include <iostream>

namespace mult
{
    void mutex_lock(Mutex& mutex)
    {
        while (mutex.lockFlag.exchange(true, std::memory_order_relaxed));
        std::atomic_thread_fence(std::memory_order_acquire);
    }

    void mutex_unlock(Mutex& mutex)
    {
        std::atomic_thread_fence(std::memory_order_release);
        mutex.lockFlag.store(false, std::memory_order_relaxed);
    }
}