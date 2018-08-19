#define AUTHOR "Andreas Schwarzmann"

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define REQ_SHTDN_C 0
#define REQ_SHTDN_S 1
#define REQ_CALCSUM 2
#define REQ_CNTNBRS 3

#define SERVER_PORT 54321

void get_request(int, short*, char*);
void set_reply(int, char*);
void handle_error(char*, int);
int calc_sum(char*);
int cnt_args(char*);

int main()
{
	printf("This solution has been created by %s\n\n", AUTHOR);

	struct sockaddr_in clientaddr, serveraddr;
	socklen_t addrlen_client;

	int sockfd, nsockfd, srvr_shdn = 0, req_len, bnd_ret;
	char req_text[1024], rep_text[1024];
	short func_id;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		handle_error("cannot create stream socket", sockfd);

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERVER_PORT);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); // BIND SOCKET TO ALL AVAILABLE INTERFACES

	// ASSIGN SERVERADDRESS TO SOCKET
	if ((bnd_ret = bind(sockfd, (struct sockaddr*) &serveraddr, sizeof(serveraddr))) < 0)
		handle_error("cannot bind stream socket", bnd_ret);

	// SERVER READY -> CREATE QUEUE FOR INCOMING CONNECTIONS
	listen(sockfd, 1);

	// GET ADDRESS-LENGTH OF CLIENT
	addrlen_client = sizeof(clientaddr);

	// WAIT FOR INCOMING CONNECTIONS
	printf("<server> waiting for connection requests\n");
	nsockfd = accept(sockfd, (struct sockaddr*) &clientaddr, &addrlen_client);

	// PRINT CLIENT INFORMATION
	printf("<server> received a connection request\n");
	printf("<server> client ip-address: %s\n", inet_ntoa(clientaddr.sin_addr));
	printf("<server> client port-number: %d\n", serveraddr.sin_port);

	while (!srvr_shdn)
	{
		bzero(req_text, sizeof(req_text)); // RESET REQUEST-TEXT-BUFFER
		bzero(rep_text, sizeof(rep_text)); // RESET REPLY-TEXT-BUFFER

		printf("<server> waiting for client function requests...\n");
		get_request(nsockfd, &func_id, req_text);
		printf("<server> request-func: %hi\n", func_id);
		printf("<server> request-msg: %s\n", req_text);

		switch (func_id)
		{
			case REQ_SHTDN_C:
				printf("<server> info: client has been disconnected\n");
				// NO REPLY NECESSARY
				break;

			case REQ_SHTDN_S:
				printf("<server> client requests to shutdown server\n");
				set_reply(nsockfd, "info: server has been disconnected\n");
				srvr_shdn = 1;
				break;

			case REQ_CALCSUM:
				printf("<server> client requests to calculate numbers\n");
				if (cnt_args(req_text) <= 12)
				{
					sprintf(rep_text, "%d", calc_sum(req_text));
					set_reply(nsockfd, rep_text);
				}
				else
					set_reply(nsockfd, "too much arguments [max. = 12]");
				break;

			case REQ_CNTNBRS:
				printf("<server> client requests to count numbers\n");
				if (cnt_args(req_text) <= 12)
				{
					sprintf(rep_text, "%d", cnt_args(req_text));
					set_reply(nsockfd, rep_text);
				}
				else
					set_reply(nsockfd, "too much arguments [max. = 12]");
				break;
		}
	}
	close(sockfd);
	exit(0);
}

void get_request(int sockfd, short *func_id, char *req_text)
{
	int read_ret, req_text_len;

	// READ REQUESTED FUNCTION ID
	if ((read_ret = read(sockfd, func_id, sizeof(short))) < 0)
		handle_error("error reading func_id", read_ret);

	*func_id = ntohs(*func_id);

	// GET LENGTH OF REQUEST TEXT
	if ((read_ret = read(sockfd, &req_text_len, sizeof(int))) < 0)
		handle_error("error reading length of text", read_ret);

	req_text_len = ntohl(req_text_len);

	// GET REQUEST TEXT
	if ((read_ret = read(sockfd, req_text, req_text_len)) < 0)
		handle_error("error reading text", read_ret);
}

void set_reply(int sockfd, char *rep_text) 
{
	char rep_buf[1024]; // BUFFER FOR REPLY
	int write_ret, rep_text_len = strlen(rep_text);

	// INIT REQUEST BUFFER (ZERO)
	bzero(rep_buf, sizeof(rep_buf));

	// SET FUNCTION-TEXT LENGTH FOR REPLY
	*((int*)&rep_buf[0]) = htonl(rep_text_len);

	// SET FUNCTION-TEXT
	strncpy(&rep_buf[sizeof(int)], rep_text, rep_text_len);

	// SEND REPLY MESSAGE
	if ((write_ret = write(sockfd, rep_buf, sizeof(int) + rep_text_len)) < 0)
		handle_error("error sending reply", write_ret);
}

void handle_error(char *err_msg, int err_nbr)
{
	printf("<server> %s\n", err_msg);
	printf("<server> errorcode: %d\n", err_nbr);
	exit(1);
}

int calc_sum(char* nbrs)
{
	int sum = 0;
	char *nbr_ptr, *temp_nbrs;
	strcpy(temp_nbrs, nbrs);

	for (nbr_ptr = strtok(temp_nbrs, " "); nbr_ptr != NULL; nbr_ptr = strtok(NULL, " "))
		sum += atoi(nbr_ptr);
	return sum;
}

int cnt_args(char* nbrs)
{
	int count = 0;
	char *nbr_ptr, *temp_nbrs; 
	strcpy(temp_nbrs, nbrs);

	for (nbr_ptr = strtok(temp_nbrs, " "); nbr_ptr != NULL; nbr_ptr = strtok(NULL, " "))
		count++;
	return count;
}
