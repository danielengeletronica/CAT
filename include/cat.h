#ifndef CAT_H
#define CAT_H

#include "ServerTCPIP.h"
#include "ClientTCPIP.h"

#define LEN 10000
using namespace std; 

//g++ master.cpp -o master -lasiopal -lopendnp3 -lasiodnp3 -pthread -lopenpal

/* This class works like a gateway.
 The cat has mathods to connecto to a client(COI),to receive the messeger,
 to read the DNP3 frame and to extract the DNP3 address.
 Based on DNP3 address, the cat controls the phase of a antenna array.
 And after that, it sends the messeger to the desired server (outstation). 
 It waits for the answer and then it sends the answer to COI (master) */
 
class Cat
{		
	protected:
		ServerTcpIP server;
		int COIPort;
		char DNP3Frame[LEN];
		int DNP3FrameLen;
		int DNP3Addr;
		
	public:
		
		int ConectToCOI(char* COIAddr, int COIPort);
		int ReadDNP3frame ();
		int GetDNP3Address ();
		int talkToOutstation (char* OutstationAddr,int port);
		void sendAnswerToCOI();
		void closeCAT();
		~Cat();
};

#endif
