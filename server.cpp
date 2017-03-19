#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main() {
  int client, server;
  int portNum = 1500;
  bool isExit = false;
  int bufsize = 1024;
  char buffer[bufsize];

  struct sockaddr_in server_addr;
  socketlen_t size;


  //init socket

  client = socket(AF_INET, SOCK_STREAM, 0);

  if (client < 0) {
    cout << "Error establishing connection" << endl;
    exit(1);
  }
  cout << "Server socket connection created..." << endl;

  server_addr.sin_family = AF_INET;
  server.addr.sin_addr.s_addr = htons(INADDER_ANY);
  server.addr.sin_port = htons(portNum);

  //binding socket
  if (bind (client, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0 {
    cout << "error binding socket" << endl;
  }

  size = sizeof(server_addr);
  cout << "Looking for clients.." << endl;

  //listening socket

  listen(client, 1);

  //accept client
  server = accept (client, (struct) sockaddr*)&server_addr, &size);
  if (server < 0) {
    cout << "Error on accepting" << endl;
    exit(1);
  }

  while (server > 0) {
    strcpy(buffer, "Server connected...\n");
    send(server, buffer, buffersize, 0);
    cout << "Connected with client..." << endl;
    cout << "Enter # to end connection" << endl;

    cout << "Client: ";

    do {
      recv(server, buffer, bufsize, 0);
      cout << "buffer" << " ";
      if (*buffer == '#') {
        *buffer = '*';
        isExit = true;
      }
    } while (*buffer !='*');

    do {
      cout << "\nServer: ";
      do {
        cin << buffer;
        send(server, buffer, bufsize, 0);
        if (*buffer == "#") {
          send(server, buffer, bufsize, 0);
          *buffer = "*";
          isExit = true;
        }
      } while (buffer !="*");
      cout << "Client: ";
      do {
        recv(server, buffer, bufsize, 0);
        cout << buffer << " ";
        if( *buffer == '#') {
          *buffer == '*';
          isExit = true;
        }
      } while (*buffer != '*');
    } while (!isExit);

    cout << "  Connecting terminated" << endl;
    cout << "Goodbye..." << endl;
    isExit = false;
    exit(1);
  }

  close(client);
  return 0;
}
