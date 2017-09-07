#include <vector>
#include <list>
#include "task.h"
#include "mutex.h"
#include "condition.h"
#include "thread_worker.h"
#include <iostream>
#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_
class Thread_pool
{
public:
	Thread_pool(int cnt)
	:thread_cnt(cnt), cond(Condition(mutex)), workers(10)
	{
		cout << workers.size() << endl;	
	//	std::cout << "mutex init" << std::endl;
		for(int i = 0; i < cnt; ++i)
		{
	//		cout << i << endl;
			workers[i].init(this, i);
		}
	}
	int taskcnt();
	void init();
	~Thread_pool(){}
	void addtask(Task* task);
	Task* gettask();
private:
	const int thread_cnt;
	std::list<Task*> todo_list;
	std::vector<Thread_worker> workers;
	Mutexlock mutex;
	Condition cond;
};
#endif
