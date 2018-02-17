/**********************************************************/
/*************************INCLUDES*************************/
/**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

/**********************************************************************/
/*************************STRUCTURE & CONSTANT ************************/
/**********************************************************************/

#define SERVER_FAILURE -1
#define STRING_SIZE 1024

int main(int argc, char* argv[])
{
	int CLIENT_Socket = 0;
	struct sockaddr_in CLIENT_SOCKADDR_IN;


 	if(argc != 4)
	{
		fprintf(stderr, "./client <name> <ip> <port>\n");
		return EXIT_FAILURE;
	}

	printf("[------------------------]\n");
	printf("[+] CLIENT DATA INFOS\n");
	printf(" Username          <+> %s\n", argv[1]);
	printf(" Internet Protocol <+> %s\n", argv[2]);
	printf(" Network Port      <+> %s\n", argv[3]);
	printf("[------------------------]\n");


	CLIENT_Socket = socket(AF_INET, SOCK_STREAM, 0);


	if(CLIENT_Socket == SERVER_FAILURE)
	{
		fprintf(stderr, "[CLIENT INFO] Server can't create socket .\n");
		perror("{:ERROR:} [!] <X>");
		goto SERVER_CLOSED;
	}

	CLIENT_SOCKADDR_IN.sin_family = AF_INET;
	CLIENT_SOCKADDR_IN.sin_port = htons(atoi(argv[3]));
	CLIENT_SOCKADDR_IN.sin_addr.s_addr = inet_addr(argv[2]);

	if(connect(CLIENT_Socket, (struct sockaddr*)&CLIENT_SOCKADDR_IN, sizeof(CLIENT_SOCKADDR_IN)) == SERVER_FAILURE)
	{
		fprintf(stderr, "[CLIENT INFO] Client impossible to connect to the server.\n");
		perror("{:ERROR:} [!] <X>");
		goto SERVER_CLOSED;
	}

	char message[STRING_SIZE] = {'\0'};
	char *_carriage_return = NULL;

	while (strcmp(message, "disconnect")) {
		printf("[+] Send a message >>> ");

		fgets(message, STRING_SIZE -1, stdin);
		_carriage_return = strchr(message, '\n');
		*_carriage_return = '\0';

		send(CLIENT_Socket, message, sizeof(message), 0);

	}

SERVER_CLOSED:
	close(CLIENT_Socket);
	return EXIT_SUCCESS;
}
