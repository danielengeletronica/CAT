#include "ClientTCPIP.h"		

/* Sockets buffers length */
#define LEN 4096 //tamanho da string do payload
	using namespace std; 
	ClientTcpIP::ClientTcpIP (char* serverAddr, int port)
	{
		this->serverAddr = serverAddr;
		this->port = port;
	}
		
	int ClientTcpIP::CreateSocket ()
	{
		fprintf(stdout, "Starting Client ...\n");
		/*
		* Creates a socket for the client
		*/
		if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
		{
			perror("Error on client socket creation:");
			return 0;
		}
		fprintf(stdout, "Client socket created with fd: %d\n", sockfd);
			
		/* Defines the connection properties */
		server.sin_family = AF_INET;         
		server.sin_port = htons(port);
		server.sin_addr.s_addr = inet_addr(serverAddr);
		memset(server.sin_zero, 0x0, 8);
		return 1;
	}
		
	int ClientTcpIP::Conect ()
	{
		int len = sizeof(server);
		if (connect(sockfd, (struct sockaddr*) &server, len) == -1)
		{
			perror("Can't connect to server");
			return 0;
		}
		return 1;
	}
		
	void ClientTcpIP::Write(char* buffer, int len)
	{
		write(sockfd, buffer, len);
		memset(buffer, 0x0, LEN);
	}
		
	int ClientTcpIP::Read(char* buffer, int len)
	{
		int message_len;
		message_len = read(sockfd, buffer, LEN);
		return message_len;
	}
		
	void ClientTcpIP::closeSocket() 
	{
		close(sockfd);
	}