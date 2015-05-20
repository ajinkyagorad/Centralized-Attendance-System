/*
 * wiznet.cpp
 *
 * Created: 08-05-2015 03:00:04 PM
 *  Author: Ajinkya
 */ 

#ifndef WIZNET_CPP_
#define WIZNET_CPP_

#include "wiznet.h"
//*******************************************
//modify the Following accordingly:

/*MAC ADDRESS OF THE ETHERNET SHIELD*/
byte mac[]={0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

/*IP Address of this Device : Default IP Address if DHCP Fails */
IPAddress ip(10,3,192,177);

/*DNS Server, Gateway, Subnet Mask */
IPAddress dnsip(10,200,1,11);
IPAddress gateway(10,3,200,250);
IPAddress subnet(255,255,224,0);

//ethernet client
///EthernetClient client;

//Server & Port to make contact

//comment above and uncomment following if server's ip address is given
//IPAddress server(10,3,0,2);



//*********************************************************
bool wiznet::init()
{
	//set default server and port for debugging/testing
	IPAddress defaultServer(10,3,192,78);
	server=defaultServer;
	port=8080;
	//initialise using manual settings 
	Serial.println("Initialising Ethernet...");
	Ethernet.begin(mac,ip,dnsip,gateway,subnet);
	//display relevant information : serial
	
	displayInfo();

}
void wiznet::displayInfo(void)
{
	Serial.print("MAC : ");	serialPrintMAC(mac);
	Serial.print("IP : ");	Serial.println(Ethernet.localIP());
	Serial.print("DNS : ");	Serial.println(Ethernet.dnsServerIP());
	Serial.print("GATEWAY : ");	Serial.println(Ethernet.gatewayIP());
	Serial.print("SUBNET : ");	Serial.println(Ethernet.subnetMask());
}
void wiznet::serialPrintMAC(byte mac[6])
{
	for(char i=0;i<5;i++)
	{
		Serial.print(mac[i],HEX);
		Serial.print(":");
	}
	Serial.println(mac[5],HEX);
}

void wiznet::setServer(IPAddress& s)
{
	server=s;
}
IPAddress wiznet::getServer(void)
{
	return server;
}
void wiznet::setPort(unsigned int p)
{
	port=p;
}
unsigned int wiznet::getPort(void)
{
	return port;
}
bool wiznet::checkWaitConnect(unsigned int timeoutSeconds)
{
	unsigned long time = millis();
	int res = 0;
	while(res!=1 && (	 (millis()-time) < timeoutSeconds*1000	) )	
	{
		res=client.connect( server,port);
	}
	client.stop();
	if(res==1)return true;	//function succeded in connnecting before  timeout
	else return false;		//function failed to connect before timeout
}
bool wiznet::startup(unsigned int timeoutSeconds)
{
	unsigned long time=millis();
	int res=0;
	if(checkWaitConnect(timeoutSeconds)==false)
	{
		//unable to connect : 
		return false;
	}
	//else go 
	while(	 (millis()-time) < timeoutSeconds*1000	)
	{
		res=client.connect( server,port);
		if(res==1)
		{
			client.println("GET /startup.php	 HTTP/1.1");
			client.print("Host: ");client.println(server);
			client.println("Connection: Close");		//connection to keep alive
			client.println();
			while(client.connected() )
			{
				if(client.available())
				{
					response=client.readString();
					Serial.println("@@@@@@@@@@@@@@@@@@");
					Serial.println(response);
					Serial.println("@@@@@@@@@@@@@@@@@@");
				}
			}
			break;
		}
	}
	client.stop();
	if(res==1)return true;	//function succeded in connnecting before  timeout
	else return false;		//function failed to connect before timeout
}
int wiznet::checkData(String method,String type,String uid,String devid, String time,String date,String lat,String lon)
{
	String data;
	
	if(client.connect(server,port))
	{
		//if connected
		//send get request with all flags
		data="METHOD="+method+"&TYPE="+type+"&UID="+uid+"&DEVID="+devid+"&TIME="+time+"&DATE="+date+"&LAT="+lat+"&LON="+lon;
		client.print("GET /usingphp.php?");client.print(data);client.println(" HTTP/1.1");
		client.print("Host: ");client.println(server);
		client.println("Connection: close");
		client.println();	//empty line
		
		while(client.connected() )		
		{
			if(client.available())
			{
				
				response=client.readString();
				
			}
		}
		
		client.stop();
		return 1;
	}
	else
	{
		//unable to connect
		dataNotSent=data;
		return -1;	//return -1  for communication error
		
	}
}

int  wiznet::processData()
{
	Serial.println("######################");
	Serial.println(response);
	Serial.println("######################");
	if(response.indexOf("NOT FOUND")>0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

String wiznet::getDataNotSent()
{
	return  dataNotSent;
}
#endif