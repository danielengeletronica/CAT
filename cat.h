#ifndef CAT_H
#define CAT_H
#include "ServerTCPIP.h"
#include "ClientTCPIP.h"

using namespace std; 

//g++ master.cpp -o master -lasiopal -lopendnp3 -lasiodnp3 -pthread -lopenpal
#define PORT 20001 //porta para conectar o tcpserver e o master
#define PORT1 20000 //porta para conectar o tcpClient com a outstation

#define BUFFER_LENGTH 4096 //tamanho do string do payload

/* Sockets buffers length */
#define LEN 4096 //tamanho da string do payload

/* endereços */
#define SERVER_ADDR "127.0.0.1" //endereço da comunicaçao entre o tcpserver e o com master
#define  SERVER_ADDR1 "127.0.0.2" //endereço entre tcpclient e o outstation

class Cat
{		
	protected:
		ServerTcpIP server;
		int COIPort;
		char* COIAddr=(char*) malloc(1*sizeof (char));
		char DNP3Frame[LEN];
		int DNP3FrameLen;
		int DNP3Addr;
		
	public:
		Cat(char* COIAddr, int COIPort);
		
		int ConectToCOI();
		
		int ReadDNP3frame ();
		
		
		int GetDNP3Address ();
		
		
		int talkToOutstation (char* OutstationAddr,int port);
		
	
	void sendAnswerToCOI();
	
	void closeCAT();
};

#endif
