	#include "ClientTCPIP.cpp"	
	#include "ServerTCPIP.cpp"
	#include "ServerTCPIP.h"
	#include "ClientTCPIP.h"
	#include "cat.h"
	
	using namespace std; 
	
	int Cat::ConectToCOI()
		{		
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
				memset(DNP3Frame, 0x0, LEN);
			
				if((DNP3FrameLen = server.Read(DNP3Frame, LEN)) < 0) 
				{
				    return 0;  
			    }
			return 1;
		}
		
		int Cat::GetDNP3Address () 
		{	
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
			ClientTcpIP client(SERVER_ADDR1, PORT1);
	
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
		server.Write(DNP3Frame,DNP3FrameLen);
	}
	
	void Cat::closeCAT()
	{
		server.closeSocket();
	}