	#include "ClientTCPIP.cpp"	
	#include "ServerTCPIP.cpp"
	#include "ServerTCPIP.h"
	#include "ClientTCPIP.h"
	#include "cat.h"
	
	using namespace std; 
	
	Cat::Cat(char* COIAddr, int COIPort)
	{
			this->COIAddr = COIAddr;
			this->COIPort = COIPort;
	}
	
	int Cat::ConectToCOI()
		{	
			/**
				* This method sets a socket connection to COI
				* @return True or False
				* @author Daniel L. S. Nascimento
				* @since  14-05-2020
				*/
			server.setAddrandPort (COIAddr, COIPort);
			
			if (!server.CreateSocket())
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
			
				if((DNP3FrameLen = server.Read(DNP3Frame, LEN)) < 0) 
				{
				    return 0;  
			    }
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
		
		int Cat::talkToOutstation (char* OutstationAddr,int port)
		{
			/**
				* This method sends the DNP3frame to the outstation 
				   based on the IP address and port and waits for the answer
				* @param OutstationAddr, IP 
				* @return True or False
				* @author Daniel L. S. Nascimento
				* @since  14-05-2020
			*/
			ClientTcpIP client(OutstationAddr,port);
	
			if (!client.CreateSocket())
			{
				return 0;
			}
		
			if (!client.Conect()){
				return 0;
			}
	
			client.Write(DNP3Frame, DNP3FrameLen);
			
			for (int i=0;i<100;i++)
			{

				if((DNP3FrameLen = client.Read(DNP3Frame, LEN)) > 0)
				{
					break;
				} 
				
				if (i==99)
				{
					return 0;
				}

			}			
		client.closeSocket();
		return 1;
	}
	
	void Cat::sendAnswerToCOI() 
	{	
		/**
			* This method sends the DNP3frame
			*  from the outstation  to COI 
			* @author Daniel L. S. Nascimento
			* @since  14-05-2020
		*/
		server.Write(DNP3Frame,DNP3FrameLen);
	}
	
	void Cat::closeCAT()
	{	/**
			* This method closes the CAT connections
			* @author Daniel L. S. Nascimento
			* @since  14-05-2020
		*/
		server.closeSocket();
	}