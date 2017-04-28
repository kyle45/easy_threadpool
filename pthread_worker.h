#include <pthread.h>
#include "task.h"
class Pthread_pool;

#ifndef PTHREAD_WORKER_H_
#define PTHREAD_WORKER_H_
class Pthread_worker
{
public:
	Pthread_worker(Pthread_pool* btp) {belong_to_pool = btp;};
	Pthread_worker() = default;
	~Pthread_worker();
	// 设置线程所属的线程池
	void set_btp(Pthread_pool *btp) {belong_to_pool = btp;}
	void init();
	void join();
	static void* routine(void* arg); // arg 是 this

	void execute();
private:
	pthread_t pthread_id;
	Task* task;
	Pthread_pool *belong_to_pool;
};
#endif