#include <rpc/pmap_clnt.h>
#include "rpc.h"

char *servername = "RPC-SERVER-VS18";

char *
vs_servername_at_1_svc(int *argp, struct svc_req *rqstp)
{
	static char result;

	printf("\n<server> client called function01: servername_at(...)\n");

	if (*argp < 0 || *argp > strlen(servername) || argp == NULL)
		result = -1;
	else
	{
		result = servername[*argp];
		printf("<server> servername: %s\n", servername);
		printf("<server> character at indexpos. %d: %c\n", *argp, result);
	}
	return &result;
}

int *
vs_strlen_1_svc(char **argp, struct svc_req *rqstp)
{
	static int result;

	printf("\n<server> client called function02: strlen(...)\n");

	if (*argp == NULL)
		result = -1;
	else
	{
		result = strlen(*argp);
		printf("<server> string-param.: %s\n", *argp);
		printf("<server> length of string: %d\n", result);
	}
	return &result;
}

int *
vs_count_char_1_svc(string_char *argp, struct svc_req *rqstp)
{
	static int result = 0;
	char *s_ptr, *s = argp->s;

	printf("\n<server> client called function03: count_char(...)\n");

	if (argp->s == NULL)
		result = -1;
	else
	{
		for (s_ptr = s; *s_ptr != '\0'; s_ptr++)
			if (*s_ptr == argp->c)
				result++;
		printf("<server> string-param.: %s\n", argp->s);
		printf("<server> char-param.: %c\n", argp->c);
		printf("<server> %c is %dx in %s\n", argp->c, result, argp->s);
	}
	return &result;
}

char **
vs_first_token_1_svc(string_char *argp, struct svc_req *rqstp)
{
	static char *result;
	char *s = argp->s, *s_ptr = strchr(s, argp->c);

	printf("\n<server> client called function04: first_token(...)\n");

	printf("<server> string-param.: %s\n", argp->s);
	printf("<server> char-param.: %c\n", argp->c);
	if (s_ptr != NULL)
	{
		printf("<server> char. found in string\n");
		*s_ptr = '\0';
	}
	else
		printf("<server> char. not found in string\n");
	result = s;
	printf("<server> first string: %s\n", result);

	return &result;
}

string_int *
vs_restandindex_bychar_1_svc(string_char *argp, struct svc_req *rqstp)
{
	static string_int result;
	char *s = argp->s, *s_ptr = strchr(s, argp->c);

	printf("\n<server> client called function05: restandindex_bychar(...)\n");
	printf("<server> string-param.: %s\n", argp->s);
	printf("<server> char-param.: %c\n", argp->c);

	if (s_ptr != NULL)
	{
		printf("<server> char. found in string\n");
		result.i = (int)(s_ptr - s);
		result.s = ++s_ptr;
	}
	else
	{
		printf("<server> char. not found in string\n");
		result.i = -1;
		result.s = "";
	}
	printf("<server> second string: %s\n", result.s);
	printf("<server> split index: %d\n", result.i);
	return &result;
}

string_string * 
vs_splitat_1_svc(string_int *argp, struct svc_req *rqstp)
{
	static string_string  result;

	printf("\n<server> client called function06: splitat(...)\n");
	printf("<server> string-param.: %s\n", argp->s);
	printf("<server> index-param.: %d\n", argp->i);

	if (argp->i < 0)
	{
		result.s1 = "";
		result.s2 = argp->s;
	}
	else if (argp->i > strlen(argp->s))
	{
		result.s1 = argp->s;
		result.s2 = ""; 
	}
	else
	{
		char *s1 = malloc(argp->i * sizeof(char));
		strncpy(s1, argp->s, argp->i);

		s1[argp->i] = '\0';
		result.s1 = s1;
		result.s2 = argp->s + argp->i;
	}
	printf("<server> first string: %s\n", result.s1);
	printf("<server> second string: %s\n", result.s2);

	return &result;
}

void *
vs_increment_1_svc(long *argp, struct svc_req *rqstp)
{
	static long result;

	printf("\n<server> client called function07: increment(...)\n");

	result = *argp + 1;
	printf("<server> long-param: %ld\n", *argp);  
	printf("<server> %ld incremented by 1 = %ld\n", *argp, result);
	return (void *) &result;
}

void *
vs_shutdown_1_svc(void *argp, struct svc_req *rqstp)
{
	static char *result;

	printf("\n<server> client called function08: shutdown(...)\n");
	pmap_unset(RPCSA01PROG, RPCSA01VERS);
	printf("<server> binder-reg. deleted\n");
	printf("<server> shutdown successful\n\n");
	exit(0);

	return (void *) &result;
}
