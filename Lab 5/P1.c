#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *print_message_function(void *args)
{
	int *id = (int *)args;
	if (*id % 5 == 0)
		sleep(5);
	else
		sleep(*id % 5);
	printf("Thread %d: Hello World!\n", *id);
	pthread_exit((void *)NULL);
}

int main()
{
	pthread_t threads[10];
	int threadId[10];
	int status[10];
	for (int i = 0; i < 10; i++)
	{
		threadId[i] = i;
		status[i] = pthread_create(&threads[i], NULL, print_message_function, (void *)&threadId[i]);
		if (i % 5 == 0)
			sleep(6);
		printf("i=%d,status=%d\n", i, status[i]);
		pthread_join(threads[i], NULL);
	}
	exit(0);
}
