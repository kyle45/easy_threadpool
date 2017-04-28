#include "pthread_worker.h"
#include "pthread_pool.h"
#include <iostream>
using namespace std;
void Pthread_worker::init()
{
	pthread_create(&pthread_id, NULL, routine, this);
}
void Pthread_worker::join()
{
	pthread_join(pthread_id, NULL);
}
void* Pthread_worker::routine(void* arg) // arg 是 this
{

	Pthread_worker* worker = (Pthread_worker*) arg;
	worker->execute();
	return NULL;
}
void Pthread_worker::execute()
{

	while (1)
	{
		belong_to_pool->notificationer.lock();

		while (belong_to_pool->todo_list.size() == 0 && !belong_to_pool->shutdown)
		{
			printf("%x  waitting\n", pthread_self());
			pthread_cond_wait(&belong_to_pool->notificationer.cond,
			                  &belong_to_pool->notificationer.mutex);
		}
		if (belong_to_pool->shutdown)
		{
			//cout << cccc++ << endl;

			belong_to_pool->notificationer.unlock();
			printf("thread %x will exit\n", pthread_self());
			pthread_exit(NULL);
		}
		//printf("thread 0x%x is starting to work\n", pthread_self());
		task = belong_to_pool->todo_list.front();


		belong_to_pool->todo_list.pop_front();
		//cout << *(int*)task->arg  << " size____" << belong_to_pool->todo_list.size() << endl;
		belong_to_pool->notificationer.unlock();

		(*(task->func))(task->arg);
	}
}
Pthread_worker::~Pthread_worker()
{
	pthread_join(pthread_id, NULL);
};
