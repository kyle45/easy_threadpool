#include "mutex.h"
#include "iostream"
using namespace std;
#ifndef CONDITION_H_
#define CONDITION_H_
class Condition
{
public:
	explicit Condition(Mutexlock& _mutex):mutex(_mutex)
	{
		cout << "cond init " << endl;
		pthread_cond_init(&cond, NULL);
	}
	~Condition()
	{
		pthread_cond_destroy(&cond);
	}
	void wait()
	{
		cout << "wait" << endl;
		pthread_cond_wait(&cond, mutex.getpmutex());
	}
	void signal()
	{
		pthread_cond_signal(&cond);
	}
	void broadcast()
	{
		pthread_cond_broadcast(&cond);
	}

private:
	Mutexlock& mutex;
	pthread_cond_t cond;
	
};
#endif
