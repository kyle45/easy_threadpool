#include <pthread.h>
#include <list>
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include "task.h"
#include "pthread_worker.h"
#include "notificationer.h"
#include "pthread_pool.h"
#include "testfunc.h"
using namespace std;



int main()
{
	pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
	Pthread_pool pth_pool;
	pth_pool.init();
	int i;
	int *argi = new int[10];
	for (i = 0; i < 10; ++i)
	{
		argi[i] = i;
		pth_pool.add_task(testfunc, &argi[i]);
	};
	sleep(10);

	return 0; 
}

