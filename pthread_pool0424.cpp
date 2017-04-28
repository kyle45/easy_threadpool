#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

class Task
{
public:
	Task() = default;
	Task(void* (*f) (void*), void* arg_)
	{
		func = f;
		arg = arg_;
	}
	~Task();
private:
	void* (*func) (void*);
	void* arg;

};
class Pthread_pool;
class Notificationer
{
public:
	Notificationer()
	{
		pthread_mutex_init(&mutex, NULL);
		pthread_cond_init(&cond, NULL);

	};
	~Notificationer()
	{
		pthread_mutex_destroy(&mutex);
		pthread_cond_destroy(&cond);
	}
	void lock(){pthread_mutex_lock(&mutex);}
	void unlock(){pthread_mutex_unlock(&mutex);}
	void signal(){pthread_cond_signal(&cond);}
	void wait(){pthread_cond_wait(&cond, &mutex);}
	void broadcast(){pthread_cond_broadcast(&cond);}
private:
	pthread_mutex_t mutex;
	pthread_cond_t cond;
};
class Pthread_worker;
class Pthread_pool
{
public:
	const int MAX_WORKERS = 10;
	Pthread_pool()
	{
		workers = new Pthread_worker[MAX_WORKERS];
		for(int i = 0; i < MAX_WORKERS; ++i)
			workers[i]->set_btp(this);
		shutdown = false;

	}
	~Pthread_pool(){};
	void add_task((void*) (*f) (void*), void* arg)
	{
		notificationer.lock();
		todo_list.push_back(new Task(f, arg));
		notificationer.unlock();
		notificationer.signal();
	}

private:
	bool shutdown;

	Pthread_worker* workers; 
	list<Task*> todo_list;
	Notificationer notificationer;
};

void* testfunc(void* arg)
{
	int t = (int*)arg;
	printf("%d\n working on thread: %x\n", t, pthread_self());
	return NULL;
}
int main()
{
 	Pthread_pool pth_pool; 
	for(int i = 0; i < 10; ++i)
	{
		pth_pool.add_task(testfunc, *i);
	}
}

class Pthread_worker
{
public:
	Pthread_worker(Pthread_pool* btp){belong_to_pool = btp;};

	~Pthread_worker(){};
	void set_btp(Pthread_pool *btp){belong_to_pool = btp;}
	void init()
	{
		pthread_create(&pthread_id, NULL, routine, this);
	}
	static void* routine(void* arg) // arg 是 this
	{
		Pthread_worker* worker = (Pthread_worker*) arg;
		worker->execute();
		return NULL;
	}
	void execute()
	{
		belong_to_pool->notificationer.lock();
		while(belong_to_pool->todo_list.size() == 0 && !belong_to_pool->shutdown)
		{
			printf("%x  waitting\n", pthread_self());
			pthread_cond_wait(&(belong_to_pool->notificationer->cond)
							  &(belong_to_pool->notificationer->mutex));
		}
		if(belong_to_pool->shutdown)
		{
			belong_to_pool->notificationer.unlock();
			printf("thread %x will exit\n", pthread_self());
			pthread_exit(NULL);
		}
		printf("thread 0x%x is starting to work\n", pthread_self());
		task = belong_to_pool->todo_list.front();
		todo_list.pop_front();
		belong_to_pool->notificationer.unlock();

		(*(task->func))(task->arg);

	}
	
private:
	pthread_t pthread_id;
	Task* task;

	Pthread_pool *belong_to_pool; 
};