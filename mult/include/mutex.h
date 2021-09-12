#pragma once
#include <atomic>

namespace mult 
{
    class Mutex
    {
    private:
        std::atomic<bool> lockFlag{false};

    public:
        void lock();
        void unlock();

    };
}
