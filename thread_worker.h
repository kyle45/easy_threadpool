#include <pthread.h>
#include "task.h"
#ifndef THREAD_WORKER_H_
#define THREAD_WORKER_H_
class Thread_pool;
class Thread_worker
{
public:
	Thread_worker()
	{
	
	}
	~Thread_worker(){}
	void execute();
	static void* routine(void* arg); //传入 this
	void init(Thread_pool* _btp, int i);

private:
	pthread_t id; // thread id
	Thread_pool *btp; // belong to pool,所属线程池
	Task *task;
	int test;
};
#endif
