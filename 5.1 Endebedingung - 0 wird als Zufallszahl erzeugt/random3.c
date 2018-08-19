#define AUTHOR "Andreas Schwarzmann"

#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define BUFFER_SIZE 5

typedef struct buffer
{
	pthread_mutex_t m;
	pthread_cond_t non_empty, non_full;
	int *rndm_nbrs;
	int size;
	int next_free, next_full;
	int count;
} *buffer_t;

buffer_t buffer_alloc(int size)
{
	buffer_t b = (buffer_t)malloc(sizeof(struct buffer));

	pthread_mutex_init(&(b->m), NULL);
	pthread_cond_init(&(b->non_full), NULL);
	pthread_cond_init(&(b->non_empty), NULL);

	b->rndm_nbrs = malloc(size * sizeof(int));
	b->size = size;
	b->next_free = b->next_full = b->count = 0;

	return b;
}

void buffer_free(buffer_t b)
{
	pthread_mutex_destroy(&(b->m));
	pthread_cond_destroy(&(b->non_full));
	pthread_cond_destroy(&(b->non_empty));
	free(b->rndm_nbrs);
	free(b);
}

void *producer(void *_b)
{
	struct buffer *b = (struct buffer *)_b;
	time_t sys_runtime = time(NULL);
	srand(sys_runtime);
	int rndm_nbr, ordr_nbr = 0;
	do
	{
		pthread_mutex_lock(&(b->m));
		while (b->count == b->size)
			pthread_cond_wait(&(b->non_full), &(b->m));

		printf("%d. random number of producer: %d\n", ++ordr_nbr, rndm_nbr = rand() % 20);
		b->rndm_nbrs[b->next_free] = rndm_nbr;

		b->next_free = (b->next_free + 1) % b->size;
		b->count++;

		pthread_cond_signal(&(b->non_empty));
		pthread_mutex_unlock(&(b->m));

	} while (rndm_nbr != 0);
	printf("producer will exit now\n");
}

void *consumer(void *_b)
{
	struct buffer *b = (struct buffer *)_b;
	int rndm_nbr, ordr_nbr = 0;
	do
	{
		pthread_mutex_lock(&(b->m));
		while (b->count == 0)
			pthread_cond_wait(&(b->non_empty), &(b->m));

		rndm_nbr = b->rndm_nbrs[b->next_full];
		printf("\t%d. random number of consumer: %d\n", ++ordr_nbr, rndm_nbr);
		b->next_full = (b->next_full + 1) % b->size;
		b->count--;

		pthread_cond_signal(&(b->non_full));
		pthread_mutex_unlock(&(b->m));

	} while (rndm_nbr != 0);
	printf("consumer will exit now\n");
}

void main(int argc, char *argv[])
{
	printf("This solution has been created by %s\n\n", AUTHOR);

	struct timeval strt, end;
	gettimeofday(&strt, NULL);

	buffer_t b;
	b = buffer_alloc(BUFFER_SIZE);
	pthread_t thread1, thread2, thread3, thread4;
	int *retval = (int *)malloc(sizeof(int));


	pthread_create(&thread1, NULL, producer, b);
	pthread_create(&thread2, NULL, consumer, b);

	//pthread_create(&thread3, NULL, producer, b);
	//pthread_create(&thread4, NULL, consumer, b);

	pthread_join(thread1, (void*)&retval);
	pthread_join(thread2, (void*)&retval);

	//pthread_join(thread3, (void*)&retval);
	//pthread_join(thread4, (void*)&retval);

	buffer_free(b);

	gettimeofday(&end, NULL);
	printf("runtime: %ld\xC2\xB5s\n", ((end.tv_sec * 1000000 + end.tv_usec) - (strt.tv_sec * 1000000 + strt.tv_usec)));
}

