void* testfunc(void* arg)
{

	int t = *(int*)arg;
	printf("%d\n working on thread: %x\n", t, pthread_self());
	return NULL;
}