all : lock1 lock2 petersons petersons_no_atomics
lock1 : lock1.cpp
	clang++ -std=c++11 -o lock1 lock1.cpp
lock2 : lock2.cpp
	clang++ -std=c++11 -o lock2 lock2.cpp
petersons : petersons.cpp
	clang++ -std=c++11 -o petersons petersons.cpp
petersons_no_atomics : petersons_no_atomics.cpp
	clang++ -std=c++11 -o petersons_no_atomics petersons_no_atomics.cpp
clean :
	rm -f lock1 lock2 petersons petersons_no_atomics
