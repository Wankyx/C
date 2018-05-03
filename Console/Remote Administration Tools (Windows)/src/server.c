#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define PORT 1337

int main(void)
{

  WSADATA wsadata;

  if(WSAStartup(MAKEWORD(2, 2), &wsadata) < 0)
  {
    fprintf(stderr, "[SERVER] WSAStartup failure\n");
    perror("Server");
    return EXIT_FAILURE;
  }

  SOCKET SERVER_Socket = 0;
  SOCKADDR_IN SOCKADDR_IN_Socket;

  SERVER_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if(SERVER_Socket < 0)
  {
    fprintf(stderr, "[SERVER] WSAStartup failure\n");
    perror("Server");
    WSACleanup();
    return EXIT_FAILURE;
  }

  SOCKADDR_IN_Socket.sin_port = htons(PORT);
  SOCKADDR_IN_Socket.sin_family = AF_INET;
  SOCKADDR_IN_Socket.sin_addr.s_addr = inet_addr("192.168.0.13");

  if(bind(SERVER_Socket, (SOCKADDR*)&SERVER_Socket, sizeof(SERVER_Socket)) == -1)
  {
    fprintf(stderr, "[SERVER] can't bind the socket with context\n");
    perror("Server");
    WSACleanup();
    return EXIT_FAILURE;
  }

  printf("[+] The socket server listen port %d\n", PORT);
  listen(SERVER_Socket, 5);

  SOCKET CLIENT_Socket = 0;
  SOCKADDR_IN SOCKADDR_IN_Csocket;
  int CLIENT_Length = sizeof(SOCKADDR_IN_Csocket);

  CLIENT_Socket = accept(SERVER_Socket, (SOCKADDR*)&SOCKADDR_IN_Csocket, &CLIENT_Length);

  printf("[+] La socket client est connecter %d .\n", CLIENT_Socket);

  closesocket(CLIENT_Socket);
  closesocket(SERVER_Socket);
  WSACleanup();
  return EXIT_SUCCESS;
}
