#include "pthread_worker.h"
#include "notificationer.h"
#include "task.h"
#include <list>
#ifndef PTHREAD_POOL_H_
#define PTHREAD_POOL_H_
class Pthread_pool
{
	friend class Pthread_worker;
public:
	const int MAX_WORKERS = 10;
	Pthread_pool();
	void join();
	void init();
	~Pthread_pool();
	void add_task(void* (*f) (void*), void* arg);
private:
	bool shutdown;
	Notificationer notificationer;
	Pthread_worker* workers;
	std::list<Task*> todo_list;
};
#endif