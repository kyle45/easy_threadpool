#include <pthread.h>

#ifndef NOTIFICATIONER_H_
#define NOTIFICATIONER_H_
class Notificationer
{
	friend class Pthread_worker;
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
	void lock() {pthread_mutex_lock(&mutex);}
	void unlock() {pthread_mutex_unlock(&mutex);}
	void signal() {pthread_cond_signal(&cond);}
	void wait() {pthread_cond_wait(&cond, &mutex);}
	void broadcast() {pthread_cond_broadcast(&cond);}
private:
	pthread_mutex_t mutex;
	pthread_cond_t cond;
};
#endif