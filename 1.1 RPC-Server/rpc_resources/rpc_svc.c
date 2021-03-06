/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "rpc.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define AUTHOR "Andreas Schwarzmann"

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static void
rpcsa01prog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		int vs_servername_at_1_arg;
		char *vs_strlen_1_arg;
		string_char vs_count_char_1_arg;
		string_char vs_first_token_1_arg;
		string_char vs_restandindex_bychar_1_arg;
		string_int vs_splitat_1_arg;
		long vs_increment_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case vs_servername_at:
		_xdr_argument = (xdrproc_t) xdr_int;
		_xdr_result = (xdrproc_t) xdr_char;
		local = (char *(*)(char *, struct svc_req *)) vs_servername_at_1_svc;
		break;

	case vs_strlen:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) vs_strlen_1_svc;
		break;

	case vs_count_char:
		_xdr_argument = (xdrproc_t) xdr_string_char;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) vs_count_char_1_svc;
		break;

	case vs_first_token:
		_xdr_argument = (xdrproc_t) xdr_string_char;
		_xdr_result = (xdrproc_t) xdr_wrapstring;
		local = (char *(*)(char *, struct svc_req *)) vs_first_token_1_svc;
		break;

	case vs_restandindex_bychar:
		_xdr_argument = (xdrproc_t) xdr_string_char;
		_xdr_result = (xdrproc_t) xdr_string_int;
		local = (char *(*)(char *, struct svc_req *)) vs_restandindex_bychar_1_svc;
		break;

	case vs_splitat:
		_xdr_argument = (xdrproc_t) xdr_string_int;
		_xdr_result = (xdrproc_t) xdr_string_string;
		local = (char *(*)(char *, struct svc_req *)) vs_splitat_1_svc;
		break;

	case vs_increment:
		_xdr_argument = (xdrproc_t) xdr_long;
		_xdr_result = (xdrproc_t) xdr_void;
		local = (char *(*)(char *, struct svc_req *)) vs_increment_1_svc;
		break;

	case vs_shutdown:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_void;
		local = (char *(*)(char *, struct svc_req *)) vs_shutdown_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	printf("This solution has been created by %s\n\n", AUTHOR);
	printf("<server> rpc-server started...\n");
	printf("<server> waiting for incoming connections...\n");

	register SVCXPRT *transp;

	pmap_unset (RPCSA01PROG, RPCSA01VERS);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, RPCSA01PROG, RPCSA01VERS, rpcsa01prog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (RPCSA01PROG, RPCSA01VERS, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, RPCSA01PROG, RPCSA01VERS, rpcsa01prog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (RPCSA01PROG, RPCSA01VERS, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
