#include "cat.h"
#include <unistd.h>
//g++ master.cpp -o master -lasiopal -lopendnp3 -lasiodnp3 -pthread -lopenpal
#define PORT 20000 //porta para conectar o tcpserver e o master
#define PORT1 20000 //porta para conectar o tcpClient com a outstation

#define BUFFER_LENGTH 4096 //tamanho do string do payload

/* Sockets buffers length */
#define LEN 4096 //tamanho da string do payload

/* endereços */
#define SERVER_ADDR "127.0.0.1" //endereço da comunicaçao entre o tcpserver e o com master
#define  SERVER_ADDR1 "127.0.0.2" //endereço entre tcpclient e o outstation
#define  SERVER_ADDR2 "127.0.0.3"
#define  SERVER_ADDR3 "127.0.0.4"

char* getIPAddress(int DNP3Address)
{
	if (DNP3Address ==3)
		return SERVER_ADDR1;
	
	if (DNP3Address ==4)
		return SERVER_ADDR2;
	
	if (DNP3Address ==5)
		return SERVER_ADDR3;
	
	return SERVER_ADDR1;
	
} 

int getPort(int DNP3Address)
{
	if (DNP3Address ==3)
		return 20000;
	
	if (DNP3Address ==4)
		return 20001;
	
	if (DNP3Address ==5)
		return 20002;
	
	return 20000;
	
}


using namespace std;
 
int main(void) {
    
	int DNP3Address;
	
	
	while (1)
	{	
		Cat *cat = new Cat (SERVER_ADDR,PORT);
		
		if (cat->ConectToCOI())
		{	
			while (1)
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
	}
	return 0;
}




