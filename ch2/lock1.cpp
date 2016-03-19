#include <iostream>
#include <atomic>
#include <cstdint>
#include <thread>
class Lock1 {
	private:
		std::atomic<bool> flag[2];
	
	public:

	void lock(uint32_t threadid);
	void unlock(uint32_t threadid);
};

void Lock1::lock(uint32_t threadid)
{
	flag[threadid] = true;
	uint32_t other_threadid = !threadid;
	while (flag[other_threadid]) {
	}
}

void Lock1::unlock(uint32_t threadid)
{
	flag[threadid] = false;
}

int counter;
Lock1 lock;

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

