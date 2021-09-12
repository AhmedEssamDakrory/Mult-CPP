#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>

namespace mult
{
	class Thread_Pool
	{
	private:
		// number of workers
		size_t n;
		std::vector<std::thread> workers;
		std::queue<std::function<void()>> tasks;
		std::condition_variable cv;
		std::mutex mtx;
		bool end;
	
	public:
		Thread_Pool(size_t _n);

		template<typename F, typename... Args>
		auto add_task(F&& func, Args&&... args)
		{
			using return_type = typename std::invoke_result<F, Args...>::type;

			auto task = std::make_shared<std::packaged_task<return_type()>>(
				std::bind(std::forward<F>(func), std::forward<Args>(args)...)
				);

			std::future<return_type> res = task->get_future();

			{
				// critical section
				std::unique_lock<std::mutex> lock(this->mtx);

				this->tasks.emplace([task]() {
					(*task)();
					});
			}

			// notify waiting thread
			this->cv.notify_one();

			return res;
		}

		~Thread_Pool();
	};
}