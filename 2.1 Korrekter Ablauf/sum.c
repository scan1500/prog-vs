#define AUTHOR "Andreas Schwarzmann"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define LENGTH 4

int field[LENGTH][2];
int sums[LENGTH];

void *add_op_thread(void *arg) 
{	
	int *input = (int*)arg, *result, i;
	
	if ((result = (int*)malloc(sizeof(int))) == NULL)
		exit(1);

	*result = input[0] + input[1];
	pthread_exit(result);
}

void main(void) 
{ 	
	printf("This solution has been created by %s\n\n", AUTHOR);

	pthread_t thread[LENGTH];
	int i, j, *result;

	if ((result = (int*)malloc(sizeof(int))) == NULL)
		exit(1);

	for (i = 0; i < LENGTH; i++)
		for (j = 0; j <= 1; j++)
			printf("field[%d][%d] = %d\n", i, j, field[i][j] = (i*2)+j);

	for (i = 0; i < LENGTH; i++)
		pthread_create(&(thread[i]), NULL, &add_op_thread, &field[i]);

	for (i = 0; i < LENGTH; i++) 
	{
		pthread_join(thread[i], (void*)&result);
		printf("result of thread %d = %d\n", i, sums[i] = *result);
		pthread_detach(thread[i]);
	} 

	for (*result = i = 0; i < LENGTH; i++)
		*result += sums[i];
	printf("final result: %d\n", *result);
}
