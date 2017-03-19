y
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>


int main() {

  int client;
  int portNum = 1500; // same port nr for client and server
  bool isExit = false;
  int bufsize = 1024;
  char buffer[buffsize];
  char* ip = "127.0.0.1";



  struct sockaddr_in server_addr;

  //creates a new socket with 3 arguments:
  //address domain of the socket, type of the socket, protocol argument(always 0)
  //this will return a small integer and is used for all refs to this socket, if it fails,
  //it will return -1
  client = socket(AF_INET, SOCK_STREAM, 0);

  //establishing connection

  if (client < 0) {
    cout << "\n Error establishing sockeet..." << endl;
    exit(1);
  }
  //create socket

  cout << "\n=> Socket has been created..." << endl;

  //server_addr is a structure of soccadr_in.
  //sin_family contains code for the address family. It should always be set to AF_INET
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(portNum);

  //returns 1 if the IP is valid and 0 if the port is invalid
  //inet_pton converts IP to packets
  //inet_ntoa converts back packets to IP

  if(connect(client, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0 ) {
    cout << "=> Connection to the server port number: " << portNum << endl;
  }

  cout << "=> Awaiting confirmation from the server..." << endl;
  recv(client,buffer,buffsize, 0);
  cout << "=> Connection confirmed";

  cout << "\n\nEnter # to end communication"

  //the client sends message first

  do {
    cout << "Client: ";
    do {
      cin >> buffer;
      send(client, buffer, bufsize, 0);
      if (*buffer == '#') {
        send(client, buffer, bufsize, 0);
        *buffer = '#';
        isExit = true;
      }
    } while (*buffer != 42);
    cout << endl;
  } while(!isExit);

  cout << "\n => Connection terminated. \nGoodbye...\n"

  close(client);
  return 0;
}
