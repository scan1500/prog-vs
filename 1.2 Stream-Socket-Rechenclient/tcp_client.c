#define AUTHOR "Andreas Schwarzmann"

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>

#define REQ_SHTDN_C 0
#define REQ_SHTDN_S 1
#define REQ_CALCSUM 2
#define REQ_CNTNBRS 3

void set_request(int, short, char*);
void get_reply(int, char*);
void handle_error(char*, int);

int main(int argc, char *argv[])
{
	printf("This solution has been created by %s\n\n", AUTHOR);

	struct hostent *hp, *gethostbyname();
	struct sockaddr_in serveraddr;

	short func_id;
	int sockfd, clnt_shdn = 0, cnct_ret;
	char req_id[10], rep_text[1024], req_text[1024];

	if (argc < 3)
		handle_error("client needs 2 arguments: <ip-address> <port-number> ", -1);

	printf("<client> building connection to server...\n");
	printf("<client> server-ip: %s\n", argv[1]);
	printf("<client> server-port: %s\n", argv[2]);

	// GET SOCKET-FILEDESCRIPTOR (HANDLE)
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		handle_error("cannot create stream socket", sockfd);

	// BUILD ADDRESS OF SERVER
	if ((hp = gethostbyname(argv[1])) == 0)
		handle_error("cannot create stream socket", 0);

	// SET SERVERADDRESS, SERVERPORT,
	bcopy((char *)hp->h_addr_list[0], (char *)&serveraddr.sin_addr, hp->h_length);
	serveraddr.sin_port = htons(atoi(argv[2]));
	serveraddr.sin_family = AF_INET;

	// TRY TO CONNECT SO SERVER
	if ((cnct_ret = connect(sockfd, (struct sockaddr*) &serveraddr, sizeof(serveraddr))) < 0)
		handle_error("error connecting to server", cnct_ret);
	printf("<client> connected to server\n");

	// CLIENT SUCCESSFULLY CONNECTED TO THE SERVER | CONTINUE CLIENT PROGRAM
	// ---------------------------------------------------------------------

	while (!clnt_shdn)
	{
		bzero(req_text, sizeof(req_text));	 // RESET REQUEST-TEXT-BUFFER
		bzero(rep_text, sizeof(rep_text));   // RESET REPLY-TEXT-BUFFER

		// GET REQUEST-ID FROM USER
		printf("<client> select server function\n");
		printf("<client> %d -> shutdown client\n", REQ_SHTDN_C);
		printf("<client> %d -> shutdown server\n", REQ_SHTDN_S);
		printf("<client> %d -> calculate a sum\n", REQ_CALCSUM);
		printf("<client> %d -> count numbers\n> ", REQ_CNTNBRS);
		fgets(req_id, sizeof(req_id), stdin);
		func_id = atoi(req_id);

		switch (func_id)
		{
			case REQ_SHTDN_C:
				// INFORM SERVER THAT CLIENT WILL DISCONNECT
				set_request(sockfd, func_id, "client will disconnect");
				printf("<client> client will exit now...\n");
				clnt_shdn = 1;
				break;

			case REQ_SHTDN_S:
				// REQUEST A SERVER SHUTDOWN
				set_request(sockfd, func_id, "shutdown by client");
				printf("<client> shutdown request send to server\n");
				// WAIT FOR SERVER RESPONSE
				printf("<client> waiting for acknowledgment\n");
				get_reply(sockfd, rep_text);
				printf("<client> %s", rep_text);
				break;

			case REQ_CALCSUM:
				// REQUEST TO CALCULATE NUMBERS
				printf("<client> input numbers to calculate\n> ");
				fgets(req_text, sizeof(req_text), stdin); // GET STRING OF NUMBERS
				set_request(sockfd, func_id, req_text);
				printf("<client> waiting for server to calculate\n> ");
				get_reply(sockfd, rep_text);
				printf("<client> the sum is: %s\n", rep_text);
				break;

			case REQ_CNTNBRS:
				printf("<client> input numbers to count\n> ");
				fgets(req_text, sizeof(req_text), stdin); // GET STRING OF NUMBERS
				set_request(sockfd, func_id, req_text);
				printf("<client> waiting for server to count numbers\n> ");
				get_reply(sockfd, rep_text);
				printf("<client> the count is: %s\n", rep_text);
				break;

			default:
				printf("<client> reqeust-id is unknown\n");
				break;
		}
	}
	close(sockfd);
	exit(0);
}

void set_request(int sockfd, short func_id, char *req_text)
{	// REQUEST MESSAGE FORMAT = [ REQ-ID(SHORT) | REQ-TEXT-LENGTH(INT) | REQ-TEXT(CHAR*) ]

	char req_buf[1024]; // BUFFER FOR REQUEST
	int req_text_len = strlen(req_text) , write_ret;

	// SET REQUEST ID
	*((short*)&req_buf[0]) = htons(func_id);

	// SET FUNCTION-TEXT LENGHT
	*((int*)&req_buf[sizeof(short)]) = htonl(req_text_len);

	// SET FUNCTION-TEXT
	strncpy(&req_buf[sizeof(short) + sizeof(int)], req_text, req_text_len);

	// SEND DATASTREAM TO SERVER
	if ((write_ret = write(sockfd, req_buf, sizeof(short) + sizeof(int) + req_text_len)) < 0)
		handle_error("error sending data to stream", write_ret);
}

void get_reply(int sockfd, char *rep_text)
{
	int read_ret, rep_len;

	// READ LENGTH OF REPLY TEXT
	if ((read_ret = read(sockfd, &rep_len, sizeof(int))) < 0)
		handle_error("error reading length of incoming stream", read_ret);

	int rep_len_host = ntohl(rep_len);
	
	// READ REPLY MESSAGE
	if ((read_ret = read(sockfd, rep_text, rep_len_host)) < 0)
		handle_error("error reading text of incoming stream", read_ret);
}

void handle_error(char *err_msg, int err_nbr)
{
	printf("<client> %s\n", err_msg);
	printf("<client> errorcode: %d\n", err_nbr);
	exit(1);
}
