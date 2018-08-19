#define AUTHOR "Andreas Schwarzmann"

#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct thread_args
{
	pthread_t thread;
	int it_nr, id;
	char name[16];
}ta[2];

void *add_threadtask(void *arg)
{
	struct thread_args *input = (struct thread_args *)arg;

	while (1)
	{
		if (input->id == 1)
			usleep(500000);
		if (input->id == 2)
			usleep(2000000);

		printf("threadname: %s | iteration-nr.: %d\n", input->name, ++input->it_nr);
	}
}

void main(void)
{
	printf("This solution has been created by %s\n\n", AUTHOR);

	int *result = (int *)malloc(sizeof(int));
	
	ta[0].id = 1;
	strcpy(ta[0].name, "thread 1");
	ta[1].id = 2;
	strcpy(ta[1].name, "thread 2");

	time_t sys_runtime = time(NULL);
	pthread_create(&(ta[0].thread), NULL, &add_threadtask, &ta[0]);
	pthread_create(&(ta[1].thread), NULL, &add_threadtask, &ta[1]);

	while (1)
		if ((time(NULL) - sys_runtime) >= 5)
		{
			pthread_cancel(ta[0].thread);
			pthread_cancel(ta[1].thread);
			break;
		}	

	//pthread_join(ta[0].thread, (void *)&result);
	//pthread_join(ta[1].thread, (void *)&result);

	printf("result of thread 1: %d\n", *result);
	printf("result of thread 2: %d\n", *result);

	pthread_detach(ta[0].thread);
	pthread_detach(ta[1].thread);


}