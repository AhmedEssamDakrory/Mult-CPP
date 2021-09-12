#include "../include/mutex.h"
#include <iostream>

namespace mult
{
    void Mutex::lock()
    {
        while (this->lockFlag.exchange(true, std::memory_order_relaxed));
        std::atomic_thread_fence(std::memory_order_acquire);
    }

    void Mutex::Mutex::unlock()
    {
        std::atomic_thread_fence(std::memory_order_release);
        this->lockFlag.store(false, std::memory_order_relaxed);
    }
}