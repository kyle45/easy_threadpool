#include <unistd.h>
#include <iostream>
#include "testfunc.h"
#include "pthread_pool.h"
using namespace std;
Pthread_pool::Pthread_pool()
{
	shutdown = false;
	workers = new Pthread_worker[MAX_WORKERS];
	// 为每个 worker 设置其所属的线程池  以及初始化
}

void Pthread_pool::init()
{
	for (int i = 0; i < MAX_WORKERS; ++i)
	{
		workers[i].init();
		workers[i].set_btp(this);
	}
}

void Pthread_pool::join()
{
	for (int i = 0; i < MAX_WORKERS; ++i)
		workers[i].join();
}
void Pthread_pool::add_task(void* (*f) (void*), void* arg)
{
	notificationer.lock();
	todo_list.push_back(new Task(f, arg));
	//cout << *(int*)(todo_list.front()->arg) << *(int*)(todo_list.back()->arg) << endl;

	//cout << &(todo_list) << endl;
	//cout << endl;
	notificationer.unlock();
	notificationer.signal();
}
void* testfunc(void* arg)
{

	int t = *(int*)arg;
	printf("%d\t working on thread: %x\n", t, pthread_self());
	sleep(1);
	return NULL;
}
Pthread_pool::~Pthread_pool()
{
	shutdown = true;
	notificationer.broadcast();
	delete[] workers;
	notificationer.lock();
	todo_list.clear();
	notificationer.unlock();

}