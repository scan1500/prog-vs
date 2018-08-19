#define AUTHOR "Andreas Schwarzmann"

#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct thread_data
{
	int rndm, sync, prmt;
}td;

void *create_rand(void *arg)
{
	struct thread_data *data = (struct thread_data *)arg;
	int ordr = 1, *retval = (int *)malloc(sizeof(int));
	*retval = 0;

	time_t sys_runtime = time(NULL);
	srand(sys_runtime);

	while (1)
	{
		if (data->sync == 0)
		{
			printf("THREAD1 - #%d: %d\n\n", ordr++, data->rndm = rand() % 20);
			data->sync = 1;
		}
		if (data->sync == 2)
			pthread_exit(retval);
	}
}

void *print_rand(void *arg)
{
	struct thread_data *data = (struct thread_data *)arg;
	int ordr = 1, *retval = (int *)malloc(sizeof(int));
	*retval = 0;

	while (1)
	{
		if (data->sync == 1)
		{
			printf("\tTHREAD2 - #%d: %d\n\n", ordr, data->rndm);

			if (ordr++ == data->prmt)
			{
				data->sync = 2;
				pthread_exit(retval);
			}
			else
				data->sync = 0;
		}
	}
}

void main(int argc, char *argv[])
{
	printf("This solution has been created by %s\n\n", AUTHOR);

	struct timeval strt, end;
	gettimeofday(&strt, NULL);

	int *result = (int *)malloc(sizeof(int));
	td.prmt = *argv[1] - 48;
	pthread_t thread[2];

	pthread_create(&thread[0], NULL, &create_rand, &td);
	pthread_create(&thread[1], NULL, &print_rand, &td);

	pthread_join(thread[0], (void *)&result);
	printf("exit code of thread 1: %d\n", *result);
	pthread_detach(thread[0]);

	pthread_join(thread[1], (void *)&result);
	printf("exit code of thread 2: %d\n", *result);
	pthread_detach(thread[1]);

	gettimeofday(&end, NULL);
	printf("runtime: %ld\xC2\xB5s\n", ((end.tv_sec * 1000000 + end.tv_usec) - (strt.tv_sec * 1000000 + strt.tv_usec)));
}