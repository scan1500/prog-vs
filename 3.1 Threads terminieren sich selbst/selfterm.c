#define AUTHOR "Andreas Schwarzmann"

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

struct thread_args
{
	pthread_t thread; 
	time_t thread_start;
	int it_nr, id;
	char name[16];
}ta[2];

void *add_threadtask(void *arg)
{
	int *result = (int *)malloc(sizeof(int));
	struct thread_args *input = (struct thread_args *)arg;
	input->thread_start = time(NULL);
	*result = 42;

	while (1)
	{		
		if (input->id == 1)
			usleep(500000); 
		if (input->id == 2)
			usleep(2000000);

		printf("threadname: %s | iteration-nr.: %d\n", input->name, ++input->it_nr);

		if ((time(NULL) - input->thread_start) >= 6)
			pthread_exit(result);
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

	pthread_create(&(ta[0].thread), NULL, &add_threadtask, &ta[0]);
	pthread_create(&(ta[1].thread), NULL, &add_threadtask, &ta[1]);

	pthread_join(ta[0].thread, (void *)&result);
	printf("return of thread 1: %d\n", *result);
	pthread_detach(ta[0].thread);

	pthread_join(ta[1].thread, (void *)&result);
	printf("return of thread 2: %d\n", *result);
	pthread_detach(ta[1].thread);
}