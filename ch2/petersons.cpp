#include <iostream>
#include <atomic>
#include <cstdint>
#include <thread>
class Petersons_lock {
	private:
		std::atomic<bool> flag[2];
		std::atomic<unsigned int> victim;
	
	public:

	void lock(unsigned int threadid);
	void unlock(unsigned int threadid);
};

void Petersons_lock::lock(unsigned int threadid)
{
	flag[threadid] = true;
	victim = threadid;
	unsigned int other_threadid = !threadid;
	while (flag[other_threadid] && victim == threadid) {
	}
}

void Petersons_lock::unlock(unsigned int threadid)
{
	flag[threadid] = false;
}

uint32_t counter;
Petersons_lock lock;

void thread1(const uint32_t count)
{
	for (uint32_t i = 0; i < count; i++) {
		lock.lock(1);
		counter++;
		lock.unlock(1);
	}
}

void thread0(const uint32_t count)
{
	for (uint32_t i = 0; i < count; i++) {
		lock.lock(0);
		counter++;
		lock.unlock(0);
	}
}

int main()
{
	for (uint32_t i = 10; i < 1000000; i+=10) {
		counter = 0;
		std::thread t(thread1, i);
		thread0(i);
		t.join();
		std::cout << "i = " << i << "counter = " << counter << std::endl;
		if (counter != i * 2) {
			std::cout << "Error Case!"<< std::endl;
			exit(0);
		}
	}
	return 0;
}

