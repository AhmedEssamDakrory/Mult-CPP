#include "../include/thread_pool.h"

namespace mult
{
	Thread_Pool::Thread_Pool(size_t _n) : end(false), n(_n)
	{
		// creating threads
		for (size_t i = 0; i < n; ++i)
		{
			this->workers.emplace_back(std::thread([this]() {
				// generic worker (accepts any type of tasks)
				while (1)
				{
					std::function<void()> task;

					{
						// critical section
						std::unique_lock<std::mutex> lock(this->mtx);

						// thread blocked as long as there is no tasks to work on
						cv.wait(lock, [this]() { return this->end || !this->tasks.empty(); });

						if (this->end && this->tasks.empty())
							return;

						// move the ownership [no need to copy]
						task = std::move(this->tasks.front());
						this->tasks.pop();
					}

					// execute task
					task();

				}
			}));
		}
	}

	Thread_Pool::~Thread_Pool()
	{
		{
			std::unique_lock<std::mutex> lock(this->mtx);
			this->end = true;
		}

		// notify all the waiting theads
		this->cv.notify_all();

		for (auto& worker : this->workers)
		{
			worker.join();
		}
		
	}
}