#include <iostream>
#include <vector>
#include <chrono>

#include "ThreadPool.h"

// º∆ ±¿‡
class timer {
public:
	timer() : t1(std::chrono::high_resolution_clock::now()) {}
	float_t elapsed() {
		return std::chrono::duration_cast<std::chrono::duration<float_t>>(
			std::chrono::high_resolution_clock::now() - t1)
			.count();
	}
	void restart() { t1 = std::chrono::high_resolution_clock::now(); }
	void start() { t1 = std::chrono::high_resolution_clock::now(); }
	void stop() { t2 = std::chrono::high_resolution_clock::now(); }
	float_t total() {
		stop();
		return std::chrono::duration_cast<std::chrono::duration<float_t>>(t2 - t1)
			.count();
	}
	~timer() {}

private:
	std::chrono::high_resolution_clock::time_point t1, t2;
};


int main()
{
	int task_cnt = 80;
	int thread_cnt = 16;

	ThreadPool pool(thread_cnt);
	std::vector< std::future<int> > results;

	timer t;
	for (int i = 0; i < task_cnt; ++i) {
		results.emplace_back(
			pool.enqueue([i] {
			std::cout << "hello " << i << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(3));
			std::cout << "world " << i << std::endl;
			return i * i;
		})
		);
	}

	for (auto && result : results)
		std::cout << result.get() << ' ';
	std::cout << std::endl;

	std::cout << "task cnt:" << task_cnt << ", total time:" << t.elapsed() << std::endl;
	return 0;
}