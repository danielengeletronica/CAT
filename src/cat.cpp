	#include "ClientTCPIP.cpp"	
	#include "ServerTCPIP.cpp"
	#include "ServerTCPIP.h"
	#include "ClientTCPIP.h"
	#include "cat.h"
	#include <memory>
	#include <csignal>
	#include <sys/socket.h>
	#define BIT0 1;
	#define BIT1 2;
	#define BIT2 3;
	#define BIT3 4;
	#define BIT4 5;
	#define BIT5 6;
	#define BIT6 7;
	#define BIT7 8;
	
	#define LEN 10000
	using namespace std; 
	
	Cat::Cat()
	{
		printf("iniciando o CAT");
	}
	
	
	int Cat::ConectToCOI(char* COIAddr, int COIPort)
	{	
			/**
				* This method sets a socket connection to COI
				* @return True or False
				* @author Daniel L. S. Nascimento
				* @since  14-05-2020
				*/
			
			if (!server.CreateSocket(COIAddr, COIPort))
			{
				return 0;
			}	
				
			if (!server.Bind()){
				return 0;
			}
			
			if (!server.Listen()){
				return 0;
			}
			
			if (!server.Accept())
			{
				return 0;
			}
			
			fprintf(stdout, "Client connected.\nWaiting for client message ...\n");
			
			return 1;
	}
		
		int Cat::ReadDNP3frame ()
		{		
				/**
				* This method receives the DNP3frame from the COI
				* @return True or False
				* @author Daniel L. S. Nascimento
				* @since  14-05-2020
				*/
				memset(DNP3Frame, 0x0, LEN);
			
				if((DNP3FrameLen = server.Read(DNP3Frame, LEN)) <= 0) 
				{
				    return 0;  
			   	 }
			   
			   	 

				int i;
			for (i = 0; i< DNP3FrameLen; i++)
			{
				printf("%d =%x --",i,DNP3Frame[i]);
			} 
			printf("\n");			
	
			return 1;
		}
		
		int Cat::GetDNP3Address () 
		{	
			/**
				* This method extracts the DNP3 address from a DNP3 frame
				* @return DNP3Address
				* @author Daniel L. S. Nascimento
				* @since  14-05-2020
			*/
			int byte1, byte2;

			if(DNP3Frame[4] >= 0xffffff00)
			{
				byte1 = (int) DNP3Frame[4] - 0xffffff00;		
			}
			
			else
			{
				byte1= (int) DNP3Frame[4]; 
			}
			
			if(DNP3Frame[5] >= 0xffffff00)
			{
				byte2= (int) DNP3Frame[5] - 0xffffff00;			
			}
			
			else
			{
				byte2= (int) DNP3Frame[5]; 
			}
			
			DNP3Addr = (byte2*0x100) + byte1;
			cout<<DNP3Addr<<endl;
			
			return (byte2*0x100) + byte1;	
		}
		
		
		int Cat::talkToOutstation (char* OutstationAddr,int port, pthread_t t1)
		{
			/**
				* This method sends the DNP3frame to the outstation 
				   based on the IP address and port and waits for the answer
				* @param OutstationAddr, IP 
				* @return True or False
				* @author Daniel L. S. Nascimento
				* @since  14-05-2020
			*/
			unique_ptr<ClientTcpIP> client(new ClientTcpIP);
			
			
			if (!client->CreateSocket(OutstationAddr, port))
			{
				return 0;
			}
		
			if (!client->Conect()){
				return 0;
			}
			
			client->Write(DNP3Frame, DNP3FrameLen);
			
		        do{
					DNP3FrameLen = client->Read(DNP3Frame, LEN, t1);	
					server.Write(DNP3Frame,DNP3FrameLen);
					printf("\n carregando\n");
		        }while(DNP3FrameLen>0);
					
			client->closeSocket();
			signal(SIGCHLD,SIG_IGN);
			
			printf ("correct!!\n");
			if (DNP3FrameLen==0)
			{
				return 0;		
			}

		return 1;
	}
	
	
	void Cat::closeCAT()
	{	/**
			* This method closes the CAT connections
			* @author Daniel L. S. Nascimento
			* @since  14-05-2020
		*/
		server.closeSocket();
	
	}
	
	Cat::~Cat(){
		printf("cleaning cat\n");
	}
