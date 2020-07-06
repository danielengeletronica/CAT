#include <stdio.h> 
#include <stdlib.h> 
#include "cat.h"
#include <unistd.h>
//g++ master.cpp -o master -lasiopal -lopendnp3 -lasiodnp3 -pthread -lopenpal
#define PORT 20000 //porta para conectar o tcpserver e o master
#define PORT1 20000 //porta para conectar o tcpClient com a outstation

#define BUFFER_LENGTH 4096 //tamanho do string do payload

/* Sockets buffers length */
#define LEN 4096 //tamanho da string do payload

/* endereços */
#define SERVER_ADDR "192.168.25.123" //endereço da comunicaçao entre o tcpserver e o com master
#define  SERVER_ADDR1 "192.168.25.125" //endereço entre tcpclient e o outstation
#define  SERVER_ADDR2 "192.168.25.127"
#define  SERVER_ADDR3 "127.0.0.4"

char* getIPAddress(int DNP3Address)
{
	if (DNP3Address ==2)
		return SERVER_ADDR1;
	
	if (DNP3Address ==3)
		return SERVER_ADDR2;
	
	return SERVER_ADDR3;
	
} 

int getPort(int DNP3Address)
{
	if (DNP3Address ==2)
		return 20000;
	
	if (DNP3Address ==3)
		return 20000;
	
	if (DNP3Address ==4)
		return 20000;
	
	return 20000;
	
}


using namespace std;
 
int test() {
    
	int DNP3Address;
	int i;	
		Cat *cat = new Cat; 
			
		if (cat->ConectToCOI(SERVER_ADDR,PORT))
		{	
		    for (i=0; i<50; i++)
			{			
				if (cat->ReadDNP3frame ())
				{	
					DNP3Address = cat->GetDNP3Address ();
					
					if (DNP3Address==0)
					{
						break;
					}

					if (cat->talkToOutstation(getIPAddress(DNP3Address),getPort(DNP3Address)))
					{	
						cat->sendAnswerToCOI();
					}
					
					else 
					{
						break;
					}
				}
				
			}
		}
		cat->closeCAT();
		delete cat;
	
	return 0;
}

int main ()
{
	int i;
	
	for (i =0; i<5; i++)
	{
		test();
	}
	
	system("./bin/br");
	
	return 0;
}




