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

/* endereços */
#define SERVER_ADDR "192.168.25.123" //endereço da comunicaçao entre o tcpserver e o com master
#define  SERVER_ADDR1 "192.168.25.125" //endereço entre tcpclient e o outstation
#define  SERVER_ADDR2 "192.168.25.127"
#define  SERVER_ADDR3 "127.0.0.4"

char* getIPAddress(int DNP3Address)
{
	if (DNP3Address ==4)
		return SERVER_ADDR1;
	
	if (DNP3Address ==5)
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

FILE *pont_arq;	


using namespace std;
 
int test() {
    
	int DNP3Address;
	int i;	
	clock_t t1, t2; 
	int dt;
	char n[2] = "\n";
	char sp[2] = " ";
	unique_ptr<Cat> cat(new Cat);
	
	
		if (cat->ConectToCOI(SERVER_ADDR,20000))
		{  
		    for (i=0; i<80; i++)
			{	
						
				if (cat->ReadDNP3frame ())
				{
					dt = 0;
					fprintf(pont_arq, "%d", dt);
					fprintf(pont_arq, "%s", sp);
					DNP3Address = cat->GetDNP3Address ();
					
					if (DNP3Address==0)
					{
						printf("nothing");
					}

					else if (cat->talkToOutstation(getIPAddress(DNP3Address),getPort(DNP3Address)))
					{	if (DNP3Address ==4)
						{
							dt = 1;
							fprintf(pont_arq, "%d", dt);
							fprintf(pont_arq, "%s", sp);
						}
						if (DNP3Address ==5)
						{
							dt = 2;
							fprintf(pont_arq, "%d", dt);
							fprintf(pont_arq, "%s", sp);
						}
					}
				   fprintf(pont_arq, "%s", n);
				}

				else {
					break;
				}

				
			}
		}
		cat->closeCAT();
		
	return 0;
}

int main ()
{
	
	pont_arq = fopen("arquivo_palavra.txt", "a");
	if(pont_arq == NULL)
  	{
 		 printf("Erro na abertura do arquivo!");
 		 exit(0);
 	}	
	int i;
	for (i=0;i<1;i++)
		{test();}
	
	system("./bin/br");
	fclose(pont_arq);
	return 0;
}




