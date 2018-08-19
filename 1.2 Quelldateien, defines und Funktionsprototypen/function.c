#include <stdio.h>

void output(int _argc, char *_argv[])
{
	int i;
	printf("This solution has been created by %s\n\n", AUTHOR);
	printf("sizeof(char)\t\t=%lu\n", sizeof(char));
	printf("sizeof(short)\t\t=%lu\n", sizeof(short));
	printf("sizeof(int)\t\t=%lu\n", sizeof(int));
	printf("sizeof(long)\t\t=%lu\n", sizeof(long));
	printf("sizeof(long long)\t=%lu\n", sizeof(long long));
	printf("sizeof(char *)\t\t=%lu\n", sizeof(char *));
	printf("sizeof(int *)\t\t=%lu\n", sizeof(int *));
	printf("sizeof(void *)\t\t=%lu\n", sizeof(void *));
	printf("sizeof(void)\t\t=%lu\n", sizeof(void));

	for (i = 0; i < _argc; i++)
		printf("%i.call-param.: %s\n", i + 1, _argv[i]);
}