#include "thread_pool.h"
#include "condition.h"
#include "thread_worker.h"
#include "mutex.h"
#include <assert.h>
#include <iostream>
using namespace std;
/*
void Thread_pool::init()
{
	for(int i = 0; i < thread_cnt; ++i)
		workers[i].init(this, i);
}
*/
void Thread_pool::addtask(Task* task)
{
	cout << "addtask" << endl;
	Mutexlockguard lock(mutex);//RAII
	todo_list.push_back(task);
	cond.signal();
}
Task* Thread_pool::gettask()
{
	cout << "get task" << endl;
	//cout << taskcnt() << endl;
	Mutexlockguard lock(mutex);
	while(todo_list.empty())
		cond.wait();
	Task* ret = todo_list.front();
	todo_list.pop_front();
	return ret;	
}
int Thread_pool::taskcnt()
{
	Mutexlockguard lock(mutex);
	return todo_list.size();
}
