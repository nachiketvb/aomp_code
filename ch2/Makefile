all : lock1 lock2 petersons petersons_no_atomics filter_lock
lock1 : lock1.cpp
	clang++ -std=c++11 -o lock1 lock1.cpp
lock2 : lock2.cpp
	clang++ -std=c++11 -o lock2 lock2.cpp
petersons : petersons.cpp
	clang++ -std=c++11 -o petersons petersons.cpp
petersons_no_atomics : petersons_no_atomics.cpp
	clang++ -std=c++11 -o petersons_no_atomics petersons_no_atomics.cpp
filter_lock : filter_lock.cpp
	clang++ -std=c++11 -o filter_lock filter_lock.cpp
clean :
	rm -f lock1 lock2 petersons petersons_no_atomics filter_lock
