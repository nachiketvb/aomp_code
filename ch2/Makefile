all : lock1 lock2
lock1 : lock1.cpp
	clang++ -std=c++11 -o lock1 lock1.cpp
lock2 : lock2.cpp
	clang++ -std=c++11 -o lock2 lock2.cpp
clean :
	rm -f lock1 lock2
