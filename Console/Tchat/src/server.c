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
	int SERVER_Socket = 0;
	struct sockaddr_in SERVER_SOCKADDR_IN;

	if(argc != 3)
	{
		fprintf(stderr, "./server <ip> <port>\n");
		return EXIT_FAILURE;
	}
	printf("[------------------------]\n");
	printf("[+] SERVER DATA RECEIVED\n");
	printf(" Internet Protocol <+> %s\n", argv[1]);
	printf(" Network Port      <+> %s\n", argv[2]);
	printf("[------------------------]\n");

	SERVER_Socket = socket(AF_INET, SOCK_STREAM, 0);

	if(SERVER_Socket == SERVER_FAILURE)
	{
		fprintf(stderr, "[SERVER INFO] Server can't create socket .\n");
		perror("{:ERROR:} [!] <X>");
		goto SERVER_CLOSED;
	}

	SERVER_SOCKADDR_IN.sin_family = AF_INET;
	SERVER_SOCKADDR_IN.sin_port = htons(atoi(argv[2]));
	SERVER_SOCKADDR_IN.sin_addr.s_addr = inet_addr(argv[1]);

	if(bind(SERVER_Socket, (struct sockaddr*)&SERVER_SOCKADDR_IN, sizeof(SERVER_SOCKADDR_IN)) == SERVER_FAILURE)
	{
		fprintf(stderr, "[SERVER INFO] Server can't bind socket with own parameter context.\n");
		perror("{:ERROR:} [!] <X>");
		goto SERVER_CLOSED;
	}

	printf("[+] Listening to the socket on port {%d}\n", htons(SERVER_SOCKADDR_IN.sin_port));

	if(listen(SERVER_Socket, 5) == SERVER_FAILURE)
	{
		fprintf(stderr, "[SERVER INFO] Server can't listening the socket.\n");
		perror("{:ERROR:} [!] <X>");
		goto SERVER_CLOSED;
	}

	int CLIENT_Socket = 0;
	struct sockaddr_in CLIENT_SOCKADDR_IN;
	socklen_t _len_CLIENT_SOCKADDR_IN = sizeof(CLIENT_SOCKADDR_IN);
	CLIENT_Socket = accept(SERVER_Socket, (struct sockaddr*)&CLIENT_SOCKADDR_IN, &_len_CLIENT_SOCKADDR_IN);

	printf("[+] CLIENT IS CONNECTED\n");
	printf("- Client is connected with socket %d of %s:%d\n", CLIENT_Socket, inet_ntoa(CLIENT_SOCKADDR_IN.sin_addr), htons(CLIENT_SOCKADDR_IN.sin_port));


	char controls[STRING_SIZE];
	char MSG_recv[STRING_SIZE];

	while(strcmp(controls, "close\n") != 0)
	{
    if(recv(CLIENT_Socket, MSG_recv, sizeof(MSG_recv), 0) != SERVER_FAILURE)
    {
      printf("[SERVER RECV] %s\n", MSG_recv);
      sprintf(MSG_recv, "LE CLIENT : %s", MSG_recv);
      send(SERVER_Socket, MSG_recv, sizeof(MSG_recv), 0);
    }
	}
SERVER_CLOSED:
	close(CLIENT_Socket);
	close(SERVER_Socket);
 	return EXIT_SUCCESS;
}
