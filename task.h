#ifndef TASK_H_
#define TASK_H_
struct Task
{
	Task() = default;
	Task(void* (*f) (void*), void* arg_)
	{
		func = f;
		arg = arg_;
	}
	~Task();
	void* (*func) (void*);
	void* arg;

};
#endif