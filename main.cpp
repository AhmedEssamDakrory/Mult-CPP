#include <iostream>
#include "mult/include/mutex.h"
#include <thread>
#include <chrono>


int main()
{
    mult::Mutex mtx;
    int cnt = 0;

    std::thread t1([&](){
        
        for (int i = 0; i < 100; ++i)
        {
            mult::mutex_lock(mtx);
            cnt = cnt + 1;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            mult::mutex_unlock(mtx);
        }
    });

    std::thread t2([&](){
        
        for (int i = 0 ; i < 100; ++i)
        {
            mult::mutex_lock(mtx);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            cnt = cnt + 2;
            mult::mutex_unlock(mtx);
        }
        
    });

    t1.join();
    t2.join();

    std::cout << "cnt: " << cnt << std::endl;
}