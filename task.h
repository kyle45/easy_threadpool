#ifndef TASK_H_
#define TASK_H_
class Task
{
public:
	Task(void* _arg):arg(_arg){};  
	virtual ~Task(){}
	virtual void* func(void *) = 0;  //interface 
	void run(){func(arg);};
protected:
	void* arg;  // parameter 
};
#endif
