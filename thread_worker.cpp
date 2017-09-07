#include "thread_worker.h"
#include "thread_pool.h"
#include <iostream>
#include <assert.h>
using namespace std;
void Thread_worker::execute()
{
	while(true)
	{
		task = btp->gettask();
		task->run();
	}
}
void* Thread_worker::routine(void* arg) //传入 this
{
	((Thread_worker*)arg) -> execute();
}
void Thread_worker::init(Thread_pool* _btp, int i)
{
	test = i;
	btp = _btp;
//	cout << "before pthread_create " << endl;
	pthread_create(&id, NULL, routine, this);
//	cout << "pthread_create success" << endl;

}
