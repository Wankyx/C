#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SOCKET_ERROR -1

int main(int argc, char* argv[])
{
	int csock = 0;
	struct sockaddr_in csockaddr;

	int i = 0;


	if(argc != 4)
	{
		fprintf(stderr, "./%s <ip> <port> <port>\n", argv[0]);
		return EXIT_FAILURE;
	}

	csock = socket(AF_INET, SOCK_STREAM, 0);

	if(csock == SOCKET_ERROR)
	{
		fprintf(stderr, "{+} Can't create socket with TCP protocol .\n");
		return EXIT_FAILURE;
	}

	csockaddr.sin_family = AF_INET;
	csockaddr.sin_port = htons(atoi(argv[2]));
	csockaddr.sin_addr.s_addr = inet_addr(argv[1]);


	for(i = 0; i < atoi(argv[3]); i++)
	{
 		csockaddr.sin_port = htons(i);
		csock = socket(AF_INET, SOCK_STREAM, 0);

		if(csock == SOCKET_ERROR)
		{
			fprintf(stderr, "{+} Can't create socket with TCP protocol .\n");
			return EXIT_FAILURE;
		}


		if(connect(csock, (struct sockaddr*)&csockaddr, sizeof(csockaddr)) != SOCKET_ERROR)
		{
			printf("[+] The port is listening : %s:%d\n", inet_ntoa(csockaddr.sin_addr), i);
		}

		close(csock);
	}

	close(csock);
	return EXIT_SUCCESS;
}
