#include <vector>
#include <cstdio>
#include <atomic>
#include <thread>
#include <iostream>

#define NUM_THREADS 4

class Filter_lock {
	private:
	std::vector<std::atomic<unsigned int> > level;
	std::vector<std::atomic<unsigned int> > victim;
	bool threads_at_higher_or_equal_level_exist(unsigned int threadid);
	unsigned int nthreads;
	public:
	Filter_lock(unsigned int num_threads) : level(num_threads),
						victim(num_threads),
						nthreads(num_threads)
	{
		for (int i = 0; i < nthreads; ++i) {
			level[i] = 0;
		}
	}
	void lock(unsigned int threadid);
	void unlock(unsigned int threadid);
};

bool Filter_lock::threads_at_higher_or_equal_level_exist(unsigned int threadid)
{
	for (int i = 0; i < nthreads; ++i) {
		if ((i != threadid) && (level[i] >= level[threadid]))
			return true;
	}
	return false;
}

void Filter_lock::lock(unsigned int threadid)
{
	for (int curr_level = 0; curr_level < nthreads; ++curr_level) {
		level[threadid] = curr_level + 1;
		victim[curr_level] = threadid; 
		while (threads_at_higher_or_equal_level_exist(threadid) &&
				victim[curr_level] == threadid)
		{
		}
	}
}

void Filter_lock::unlock(unsigned int threadid)
{
	level[threadid] = 0;
}

uint32_t counter;
Filter_lock lock(NUM_THREADS);


void thread_func(const uint32_t count, const unsigned int threadid)
{
	for (uint32_t i = 0; i < count; ++i) {
		lock.lock(threadid);
		counter++;
		lock.unlock(threadid);
	}
}

int main()
{
	for (uint32_t i = 10; i <= 10000000; i*=10) {
		counter = 0;
		std::thread threads[NUM_THREADS];
		for (int j = 0; j < NUM_THREADS; ++j) {
			threads[j] = std::thread(thread_func, i, j);
		}
		for (int j = 0; j < NUM_THREADS; ++j) {
			threads[j].join();
		}
		std::cout << "i = " << i << " counter = " << counter << std::endl;
		if (counter != i * NUM_THREADS) {
			std::cout << "Error Case!"<< std::endl;
			exit(0);
		}
	}
	return 0;
}
