#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

#include "mult/include/mutex.h"
#include "mult/include/thread_pool.h"

int main()
{
	const int N = (int)1e5;
	{
		std::vector<std::future<int>> results;
		auto start = std::clock();

		for (int i = 0; i < N; ++i)
		{
			std::packaged_task<int()> task([]() {
				return 10;
			});
			auto res = task.get_future();
			results.emplace_back(std::move(res));
			std::thread(std::move(task)).detach();
		}

		for (auto&& res : results)
		{
			res.wait();
		}

		auto end = std::clock();
		std::cout << "total time: " << (end - start) / CLOCKS_PER_SEC << std::endl;
	}

	{
		std::vector<std::future<int>> results;
		auto start = std::clock();
		mult::Thread_Pool tpool(100);

		for (int i = 0; i < N; ++i)
		{
			auto res = tpool.add_task([]() { return 7; });
			results.emplace_back(std::move(res));
		}

		for (auto&& res : results)
		{
			res.wait();
		}

		auto end = std::clock();
		std::cout << "total time: " << (end - start) / CLOCKS_PER_SEC << std::endl;
	}

	return 0;
}