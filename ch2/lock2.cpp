#include <iostream>
#include <atomic>
#include <cstdint>
#include <thread>
class Lock2 {
	private:
		std::atomic<uint32_t> victim;
	
	public:

	void lock(uint32_t threadid);
	void unlock(uint32_t threadid);
};

void Lock2::lock(uint32_t threadid)
{
	victim = threadid;
	while (victim  == threadid) {
	}
}

void Lock2::unlock(uint32_t threadid)
{
}

int counter;
Lock2 lock;

void thread1(const int count)
{
	for (int i = 0; i < count; i++) {
		lock.lock(1);
		counter++;
		lock.unlock(1);
	}
}

void thread0(const int count)
{
	for (int i = 0; i < count; i++) {
		lock.lock(0);
		counter++;
		lock.unlock(0);
	}
}

int main()
{
	for (int i = 10; i < 1000000; i+=10) {
		counter = 0;
		std::thread t(thread1, i);
		thread0(i);
		t.join();
		std::cout << "i = " << i << "counter = " << counter << std::endl;
	}
	return 0;
}

