#include <stdio.h> 
#include <stdlib.h> 
#include "cat.h"
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <cfloat>
#include <memory>
#include <cmath> 
#include <csignal>

/* endereços */
#define SERVER_ADDR "127.0.0.2" //endereço da comunicaçao entre o tcpserver e o com master
#define  SERVER_ADDR1 "127.0.0.1" //endereço entre tcpclient e o outstation
#define  SERVER_ADDR2 "192.168.25.127"
#define  SERVER_ADDR3 "127.0.0.4"

char* getIPAddress(int DNP3Address)
{
	if (DNP3Address ==10)
		return SERVER_ADDR1;
	
	if (DNP3Address ==5)
		return SERVER_ADDR2;
	
	return SERVER_ADDR3;
	
} 

int getPort(int DNP3Address)
{
	if (DNP3Address ==10)
		return 20000;
	
	if (DNP3Address ==3)
		return 20000;
	
	if (DNP3Address ==4)
		return 20000;
	
	return 20000;
	
}


using namespace std;
 
int main() {
    
	int DNP3Address;
	int i;	
	unique_ptr<Cat> cat(new Cat);
	pthread_t t1;
   while(1){
		if (cat->ConectToCOI(SERVER_ADDR,20001))
		{  
		    for (i =0; i<80;i++)
			{	
						
				if (cat->ReadDNP3frame ())
				{
					
					DNP3Address = cat->GetDNP3Address ();
					
					if (DNP3Address==0)
					{
						printf("nothing");
						break;
					}
					cat->talkToOutstation(getIPAddress(DNP3Address),getPort(DNP3Address),t1);
				}

				else {
					break;
				}

				
			}
		
		}
	cat->closeCAT();
	
   }
	return 0;
}

