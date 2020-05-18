#ifndef SERVERTCPIP_H
#define SERVERTCPIP_H
/* Sockets buffers length */
#define LEN 4096 //tamanho da string do payload
#include<string>
#include<iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
using namespace std; 
class ServerTcpIP
{	
	protected:
		int serverfd, clientfd;
		struct sockaddr_in client, server;
		char* serverAddr = (char*) malloc(1*sizeof (char));
		int port;
		
	public:
		void setAddrandPort (char* serverAddr, int port);
		int CreateSocket ();
		int Bind();
		int Listen ();
		int Accept ();
		int Read (char* buffer, int len);
		void Write (char* buffer, int len);
		void closeSocket ();	
};

#endif