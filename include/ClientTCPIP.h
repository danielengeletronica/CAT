#ifndef CLIENTTCPIP_H
#define CLIENTTCPIP_H

/* Sockets buffers length */
#define LEN 10000 //tamanho da string do payload
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

class ClientTcpIP
{	
	protected:
		struct sockaddr_in server;
		int sockfd;
		int connected;
		int port;	
	public:
		int CreateSocket (char* serverAddr, int port);
		int Conect ();
		void Write(char* buffer, int len);
		int Read(char* buffer, int len);
		void closeSocket();
		~ClientTcpIP();
};

#endif
