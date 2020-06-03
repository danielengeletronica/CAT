#include "cat.h"
#include <unistd.h>
//g++ master.cpp -o master -lasiopal -lopendnp3 -lasiodnp3 -pthread -lopenpal
#define PORT 20001 //porta para conectar o tcpserver e o master
#define PORT1 20000 //porta para conectar o tcpClient com a outstation

#define BUFFER_LENGTH 4096 //tamanho do string do payload

/* Sockets buffers length */
#define LEN 4096 //tamanho da string do payload

/* endereços */
#define SERVER_ADDR "127.0.0.1" //endereço da comunicaçao entre o tcpserver e o com master
#define  SERVER_ADDR1 "127.0.0.2" //endereço entre tcpclient e o outstation

using namespace std;
 
int main(void) {

    Cat cat (SERVER_ADDR,PORT);
	int DNP3Address;
	
	while (1)
	{	
		if (cat.ConectToCOI())
		{	
			int i = 0;
			while (1)
			{			
				if (cat.ReadDNP3frame ())
				{	
					DNP3Address = cat.GetDNP3Address ();
					
					if (DNP3Address==0)
					{
						break;
					}
					printf("\n\nTempo 3s\n\n");
					usleep(3000000);
					
					if (cat.talkToOutstation(SERVER_ADDR1,PORT1))
					{
						cat.sendAnswerToCOI();
					}
				}
				
				else 
				{	
					i++;
					if (i==10)
						break;
				}
				
			}
			cat.closeCAT();
		}
	}
	return 0;
}
