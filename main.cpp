#include <pthread.h>
#include "thread_pool.h"
#include <iostream>
#include <unistd.h>
#include <vector>
using namespace std;

Thread_pool thpool(10);
class Mytask : public Task
{
public:
	Mytask(void* _arg):Task(_arg){}
	void* func(void*)
	{
		cout << pthread_self() << "---";
		cout << *(int*)arg << endl;
		sleep(1);
	}


};
class Mytask2 : public Task
{
public:
	Mytask2(void* _arg):Task(_arg){}
	void* func(void*)
	{
		while(true)
		{
			int in;
			cin >> in;
			if(in == 0)
			{
	 			int *pa = new int(6666666);
	 			Task *task = new Mytask(pa);			
				thpool.addtask(task);	
			}
		}
	}
};
int main()
{
	Task *task = new Mytask2(NULL);
	thpool.addtask(task);
	sleep(1);
	for(int i = 0; i < 19; ++i)
	{
		int *pa = new int(i);
		Task *task = new Mytask((void*)pa);
		thpool.addtask(task); // 扔进去 30 个任务指针，每个任务打印pid和数字后 sleep 一秒
		sleep(1);
	}
	sleep(3);
	sleep(5);
	return 0;
}
