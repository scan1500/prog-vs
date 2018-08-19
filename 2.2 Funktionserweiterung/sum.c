#define AUTHOR "Andreas Schwarzmann"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#define LENGTH 4

struct thread_args
{
	pthread_t thread;
	int id, field[2];
}ta[LENGTH];

void *add_op_thread(void *arg)
{
	int *result, i;
	struct thread_args *input = (struct thread_args *)arg;

	if ((result = (int*)malloc(sizeof(int))) == NULL)
	{
		perror(NULL);
		exit(1);
	}

	printf("starting thread %d, waiting %ds\n", input->id, input->id + 1);
	sleep(input->id + 1);
	printf("\nending thread %d, result = %d\n", input->id, *result = input->field[0] + input->field[1]);
	pthread_exit(result);
}

void main(void)
{
	printf("This solution has been created by %s\n\n", AUTHOR);

	time_t cur_time = time(NULL);
	printf("\ncurrent time: %ssystem time: %lds\n\n", ctime(&cur_time), cur_time);

	int i, j, *result, thread_retval[LENGTH], sums[LENGTH];

	if ((result = (int*)malloc(sizeof(int))) == NULL)
	{
		perror(NULL);
		exit(1);
	}

	for (i = 0; i < LENGTH; i++)
	{
		printf("param. for thread %d: \n", ta[i].id = i);
		printf("thread arg 1 = %d\n", ta[i].field[0] = (i * 2) + 0);
		printf("thread arg 2 = %d\n\n", ta[i].field[1] = (i * 2) + 1);
	}

	for (i = 0; i < LENGTH; i++)
		thread_retval[i] = pthread_create(&(ta[i].thread), NULL, &add_op_thread, &ta[i]);

	for (i = 0; i < LENGTH; i++)
	{
		pthread_join(ta[i].thread, (void*)&result);
		printf("result of thread %d = %d\n", i, sums[i] = *result);
		printf("return of thread %d = %d\n", i, thread_retval[i]);
		pthread_detach(ta[i].thread);
	}

	for (*result = i = 0; i < LENGTH; i++)
		*result += sums[i];
	printf("\nfinal result: %d\n", *result);

	cur_time = time(NULL);
	printf("\ncurrent time: %ssystem time: %lds\n\n", ctime(&cur_time), cur_time);
}
