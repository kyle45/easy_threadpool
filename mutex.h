#include <pthread.h>
#include <iostream>
using namespace std;
#ifndef MUTEXLOCK_H_
#define MUTEXLOCK_H_
class Mutexlock
{
public:
	Mutexlock()
	{
	//	cout << "lock init" << endl;
		pthread_mutex_init(&mutex, NULL);
	}
	~Mutexlock()
	{
		pthread_mutex_destroy(&mutex);
	}
	pthread_mutex_t* getpmutex()
	{
		return &mutex;
	}
	pthread_mutex_t& getrmutex()
	{
		return mutex;		
	}
	void lock()
	{
//		cout << "lock" << endl;
		pthread_mutex_lock(&mutex);
//		cout << "after lock" << endl;
	}
	void unlock()
	{
		pthread_mutex_unlock(&mutex);
	}
private:
	pthread_mutex_t mutex;
};

class Mutexlockguard
{
public:
	explicit Mutexlockguard(Mutexlock& _mutex):mutex(_mutex)
	{
//		cout << "Mutexlockguard" << endl;
		mutex.lock();
//		cout << "locked---" << endl;
	}
	~Mutexlockguard()
	{
		mutex.unlock();
	}
	Mutexlock* getpmutex()
	{
		return &mutex;
	}
private:
	Mutexlock& mutex;
};
#endif
