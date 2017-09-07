main: main.o thread_pool.o thread_worker.o
	g++ main.o thread_pool.o thread_worker.o -o out  -std=c++11 -lpthread
main.o: main.cpp
	g++ -c main.cpp
thread_pool.o: thread_pool.cpp 
	g++ -c thread_pool.cpp 
thread_worker.o: thread_worker.cpp
	g++ -c thread_worker.cpp
clean:
	rm -f *.o 
