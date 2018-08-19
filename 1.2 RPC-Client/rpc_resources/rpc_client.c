#define AUTHOR "Andreas Schwarzmann"

#include "rpc.h"

void rpcsa01prog_1(char *host, int shdn)
{
	CLIENT *clnt;
	char  *result_1;
	int  vs_servername_at_1_arg;
	int  *result_2;
	char *vs_strlen_1_arg;
	int  *result_3;
	string_char  vs_count_char_1_arg;
	char **result_4;
	string_char  vs_first_token_1_arg;
	string_int  *result_5;
	string_char  vs_restandindex_bychar_1_arg;
	string_string  *result_6;
	string_int  vs_splitat_1_arg;
	void  *result_7;
	long  vs_increment_1_arg;
	void  *result_8;
	char *vs_shutdown_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, RPCSA01PROG, RPCSA01VERS, "tcp");
	if (clnt == NULL) 
	{
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	if (shdn == 0)
	{
		// TASK #1 - NO ERROR
		vs_servername_at_1_arg = 5;
		printf("<client> get servername at position %d\n", vs_servername_at_1_arg);
		result_1 = vs_servername_at_1(&vs_servername_at_1_arg, clnt);
		if (result_1 == (char *)NULL)
			clnt_perror(clnt, "call failed");
		else if ((int)*result_1 == -1)
			printf("<client> Error: %d\n", (int)*result_1);
		else
			printf("<client> %c\n", *result_1);

		// TASK #1 - ON ERROR
		vs_servername_at_1_arg = 20;
		printf("<client> get servername at position %d\n", vs_servername_at_1_arg);
		result_1 = vs_servername_at_1(&vs_servername_at_1_arg, clnt);
		if (result_1 == (char *)NULL)
			clnt_perror(clnt, "call failed");
		else if ((int)*result_1 == -1)
			printf("<client> error: %d\n", (int)*result_1);
		else
			printf("<client> result: %c\n", *result_1);

		// TASK #2 - NO ERROR
		vs_strlen_1_arg = "bananarama";
		printf("<client> get length of string \"%s\"\n", vs_strlen_1_arg);
		result_2 = vs_strlen_1(&vs_strlen_1_arg, clnt);
		if (result_2 == (int *)NULL)
			clnt_perror(clnt, "<client> call failed");
		else if (*result_2 == -1)
			printf("<client> error: %d\n", *result_2);
		else
			printf("<client> length: %d\n", *result_2);

		// TASK #2 - ON ERROR (CALL)
		vs_strlen_1_arg = NULL;
		printf("<client> get length of string \"%s\"\n", vs_strlen_1_arg);
		result_2 = vs_strlen_1(&vs_strlen_1_arg, clnt);
		if (result_2 == (int *)NULL)
			clnt_perror(clnt, "<client> call failed");
		else if (*result_2 == -1)
			printf("<client> error: %d\n", *result_2);
		else
			printf("<client> length: %d\n", *result_2);

		// TASK #3 - NO ERROR
		vs_count_char_1_arg.c = 'a';
		vs_count_char_1_arg.s = "bananarama";
		printf("<client> count of '%c' in \"%s\"\n", vs_count_char_1_arg.c, vs_count_char_1_arg.s);
		result_3 = vs_count_char_1(&vs_count_char_1_arg, clnt);
		if (result_3 == (int *)NULL)
			clnt_perror(clnt, "<client> call failed");
		else
			printf("<client> result: %d\n", *result_3);

		// TASK #3 - NO ERROR
		vs_count_char_1_arg.c = 'a';
		vs_count_char_1_arg.s = NULL;
		printf("<client> count of '%c' in \"%s\"\n", vs_count_char_1_arg.c, vs_count_char_1_arg.s);
		result_3 = vs_count_char_1(&vs_count_char_1_arg, clnt);
		if (result_3 == (int *)NULL)
			clnt_perror(clnt, "<client> call failed");
		else if (*result_3 == -1)
			printf("<client> error: %d\n", *result_2);
		else
			printf("<client> result: %d\n", *result_3);

		// TASK #4 CHAR IS IN STRING
		vs_first_token_1_arg.c = 'r';
		vs_first_token_1_arg.s = "bananarama";
		printf("<client> split \"%s\" at '%c'\n", vs_first_token_1_arg.s, vs_first_token_1_arg.c);
		result_4 = vs_first_token_1(&vs_first_token_1_arg, clnt);
		if (result_4 == (char **)NULL)
			clnt_perror(clnt, "<client> call failed");
		else
			printf("<client> result: %s\n", *result_4);

		if ((clnt_freeres(clnt, (xdrproc_t)xdr_string, (void*)result_4)) == 0)
			clnt_perror(clnt, "clnt_freeres");

		// TASK #4 CHAR NOT IN STRING
		vs_first_token_1_arg.c = 'x';
		vs_first_token_1_arg.s = "bananarama";
		printf("<client> split \"%s\" at '%c'\n", vs_first_token_1_arg.s, vs_first_token_1_arg.c);
		result_4 = vs_first_token_1(&vs_first_token_1_arg, clnt);
		if (result_4 == (char **)NULL)
			clnt_perror(clnt, "<client> call failed");
		else
			printf("<client> result: %s\n", *result_4);

		if ((clnt_freeres(clnt, (xdrproc_t)xdr_string, (void*)result_4)) == 0)
			clnt_perror(clnt, "clnt_freeres");

		// TASK #5 CHAR IS IN STRING
		vs_restandindex_bychar_1_arg.c = 'r';
		vs_restandindex_bychar_1_arg.s = "bananarama";
		result_5 = vs_restandindex_bychar_1(&vs_restandindex_bychar_1_arg, clnt);
		if (result_5 == (string_int *)NULL)
			clnt_perror(clnt, "<client> call failed");
		else
			printf("<client> index: %d, result: %s\n", result_5->i, result_5->s);

		if ((clnt_freeres(clnt, (xdrproc_t)xdr_string_int, (void*)result_4)) == 0)
			clnt_perror(clnt, "clnt_freeres");

		// TASK #5 CHAR IS NOT IN STRING
		vs_restandindex_bychar_1_arg.c = 'x';
		vs_restandindex_bychar_1_arg.s = "bananarama";
		result_5 = vs_restandindex_bychar_1(&vs_restandindex_bychar_1_arg, clnt);
		if (result_5 == (string_int *)NULL)
			clnt_perror(clnt, "<client> call failed");
		else
			printf("<client> index: %d, result: %s\n", result_5->i, result_5->s);

		if ((clnt_freeres(clnt, (xdrproc_t)xdr_string_int, (void*)result_4)) == 0)
			clnt_perror(clnt, "clnt_freeres");

		// TASK #6 INDEX < 0
		vs_splitat_1_arg.i = -5;
		vs_splitat_1_arg.s = "bananarama";
		result_6 = vs_splitat_1(&vs_splitat_1_arg, clnt);
		if (result_6 == (string_string *)NULL)
			clnt_perror(clnt, "<client> call failed");
		else
			printf("<client> s1: %s, s2: %s\n", result_6->s1, result_6->s2);

		if ((clnt_freeres(clnt, (xdrproc_t)xdr_string_string, (void*)result_4)) == 0)
			clnt_perror(clnt, "clnt_freeres");

		// TASK #6 INDEX > STRING-LENGTH
		vs_splitat_1_arg.i = 20;
		vs_splitat_1_arg.s = "bananarama";
		result_6 = vs_splitat_1(&vs_splitat_1_arg, clnt);
		if (result_6 == (string_string *)NULL)
			clnt_perror(clnt, "<client> call failed");
		else
			printf("<client> s1: %s, s2: %s\n", result_6->s1, result_6->s2);

		if ((clnt_freeres(clnt, (xdrproc_t)xdr_string_string, (void*)result_4)) == 0)
			clnt_perror(clnt, "clnt_freeres");

		// TASK #6 INDEX > 0 && INDEX < STRING-LENGTH
		vs_splitat_1_arg.i = 6;
		vs_splitat_1_arg.s = "bananarama";
		result_6 = vs_splitat_1(&vs_splitat_1_arg, clnt);
		if (result_6 == (string_string *)NULL)
			clnt_perror(clnt, "<client> call failed");
		else
			printf("<client> s1: %s, s2: %s\n", result_6->s1, result_6->s2);

		if ((clnt_freeres(clnt, (xdrproc_t)xdr_string_string, (void*)result_4)) == 0)
			clnt_perror(clnt, "clnt_freeres");

		// TASK #7
		vs_increment_1_arg = 5;
		result_7 = vs_increment_1(&vs_increment_1_arg, clnt);
		if (result_7 == (void *)NULL)
			clnt_perror(clnt, "<client> call failed");
		else
			printf("<client> %ld incremented\n", vs_increment_1_arg);
	}
	else
	{
		// TASK #8
		vs_shutdown_1_arg = "";
		printf("<client> shutdown server by client...\n");
		result_8 = vs_shutdown_1((void*)&vs_shutdown_1_arg, clnt);
		if (result_8 == (void *)NULL)
			clnt_perror(clnt, "<client> call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}

int main (int argc, char *argv[])
{
	printf("This solution has been created by %s\n\n", AUTHOR);

	if (argc < 2) 
	{
		printf("usage: %s <hostename> <shutdown>\n", argv[0]);
		exit (1);
	}
	rpcsa01prog_1(argv[1], atoi(argv[2])); // argv[1] = HOSTNAME; 
	exit(0);
}
