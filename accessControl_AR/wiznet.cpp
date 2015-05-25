/*
 * wiznet.cpp
 *
 * Created: 08-05-2015 03:00:04 PM
 *  Author: Ajinkya
 */ 

#ifndef WIZNET_CPP_
#define WIZNET_CPP_
#include "time.h"
#include "devid.h"
#include "wiznet.h"
#include <string.h>
#include <MemoryFree.h>
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
		Serial.print("**free MEMEORY :");
		Serial.println(freeMemory(),DEC);
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
	//try few times so if it  fails first time
	while(	(millis()-time) < timeoutSeconds*1000	)
	{
		res=client.connect( server,port);
		if(res==1)
		{
			client.print("GET /cas/startup.php?DEVID=");client.print(dev.getDeviceId());client.println(" HTTP/1.1");
			client.print("Host: ");client.println(server);
			client.println("Connection: Close");		//connection to keep close
			client.println();
			while(client.connected() )
			{
				if(client.available())
				{
					client.readBytesUntil(0x00,response,1024);
					/*Serial.println("=-=-=-=-=-=-=-=-=-");
					Serial.println(response);
					Serial.println("-=-=-=-=-=-=-=-=-=");*/
					//response="NULL";
				}
			}
			
			break;
		}
	}
	client.stop();
	//setStartupSettings();
	if(res==1)return true;	//function succeded in connnecting before  timeout
	else return false;		//function failed to connect before timeout

}
/*

void wiznet::setStartupSettings()
{
	
	int  index=response.indexOf("DEVID=");
	
	if(index>=0)
	{
		String DEVID=response.substring(index+6,index+6+4);
		dev.setDeviceId(DEVID);
		Serial.print(F("!Device ID set to "));Serial.println(DEVID);
	}
	index=response.indexOf(F("METHOD="));
	if(index>=0)
	{
		int CR_index=response.indexOf("\r",index);
		String _method=response.substring(index+7,CR_index);
		dev.setDeviceMethod(_method);
	}
	index=response.indexOf("TEXTLCD=");
	if(index>=0)
	{
		int CR_index=response.indexOf("\r",index);
		String _lcd_default=response.substring(index+8,CR_index);
		dev.setLcdDefaultText(_lcd_default);
	}
	index=response.indexOf(F("DATETIME="));
	if(index>=0)
	{
		int CR_index=response.indexOf("\r",index);
		String _date_time=response.substring(index+9,CR_index);
		Serial.print(F("date_TIME :"));Serial.println(_date_time);
		timeManage.setDateTime_YmdHis(_date_time);
	}
}*/
int wiznet::checkData(String method,String type,String uid,String devid, String time,String date,String lat,String lon)
{
	String data;
	
	if(client.connect(server,port))
	{
		//if connected
		//send get request with all flags
		//data="METHOD="+method+"&TYPE="+type+"&UID="+uid+"&DEVID="+devid+"&TIME="+time+"&DATE="+date+"&LAT="+lat+"&LON="+lon;
		
		data="METHOD=";
		data=data+method;
		data=data+"&DEVID=";
		data=data+devid;
		data=data+"&TYPE=";
		data=data+type;
		data=data+"&UID=";
		data=data+uid;
		data=data+"&TIME=";
		data=data+time;
		data=data+"&DATE=";
		data=data+date;
		data=data+"&LAT=";
		data=data+lat;
		data=data+"&LON=";
		data=data+lon;
		/*Serial.println(data);
		char buf[100];
		for(int i=0;i<data.length();i++)
		{
			buf[i]=data.charAt(i);
			if(i>=100)
			{
				buf[100]=0;
			}
		}*/
		client.print(F("GET /cas/check.php?"));
		//client.print("&METHOD="+method+"&TYPE="+type+"&UID="+uid+"DEVID="+devid+"&TIME="+time+"&DATE="+date+"&LAT="+lat+"&LON="+lon);
		client.print(data);
		client.println(F(" HTTP/1.1"));
		client.print(F("Host: "));client.println(server);
		client.println(F("Connection: close"));
		client.println();	//empty line
		
		while(client.connected() )		
		{
			if(client.available())
			{
				
				//response=client.readString();
				client.readBytesUntil('\r',response,1024);
				//response="NULL";
				
			}
		}
		client.stop();
		client.flush();
		return 1;
	}
	else
	{
		//unable to connect
		//dataNotSent=data;
		return -1;	//return -1  for communication error
		
	}
}

int  wiznet::processData()
{
	
	Serial.println(F("######################"));
	Serial.println(response);
	//int res = response.indexOf(F("NOT FOUND"));
	char * loc=strstr(response,"NOT FOUND");
	Serial.println(freeMemory(),DEC);
	if(loc==NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

String wiznet::getDataNotSent()
{
	return  "NULL";
}
#endif