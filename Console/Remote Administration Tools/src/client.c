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
  int sock = 0;
  struct sockaddr_in SOCKADDR_IN_Socket;
  char _send[MEGA_OCTET];
  char* _cariage_return = NULL;
  const char* user = getenv("HOME");


  sock = socket(AF_INET, SOCK_STREAM, 0);

  if(sock == SOCKET_ERROR)
  {
    fprintf(stderr, "[CLIENT] Error can't create socket .\n");
    perror("[SERVER INFOS] <!>");
    return EXIT_FAILURE;
  }

  SOCKADDR_IN_Socket.sin_family = AF_INET;
  SOCKADDR_IN_Socket.sin_port = htons(SERVER_PORT);
  SOCKADDR_IN_Socket.sin_addr.s_addr = inet_addr("127.0.0.100");

  if(connect(sock, (struct sockaddr*)&SOCKADDR_IN_Socket, sizeof(SOCKADDR_IN_Socket)) == SOCKET_ERROR)
  {
    fprintf(stderr, "[SERVER] Error connect to the server .\n");
    perror("[SERVER INFOS] <!>");
    close(sock);
    return EXIT_FAILURE;
  }

  sprintf(_send, "[+] %s is connected !", user);
  send(sock, _send, sizeof(_send), 0);

  while(strcmp(_send, "exit") != 0)
  {
    printf("[%s] SEND >>> ", user);
    fgets(_send, MEGA_OCTET-1, stdin);
    _cariage_return = strchr(_send, '\n');
    *_cariage_return = '\0';

    send(sock, _send, sizeof(_send), 0);
  }

  close(sock);
  return EXIT_SUCCESS;
}
