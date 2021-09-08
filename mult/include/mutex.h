#pragma once
#include <atomic>

namespace mult 
{
    typedef struct Mutex
    {
        std::atomic<bool> lockFlag{false};
    } Mutex;

    void mutex_lock(Mutex& mutex);

    void mutex_unlock(Mutex& mutex);
}
