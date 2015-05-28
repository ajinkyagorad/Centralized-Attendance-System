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
	//IPAddress defaultServer(54,165,174,126); 
	server=defaultServer;
	port=8080;
	//initialise using manual settings 
	Serial.println("Initialising Ethernet...");
	Ethernet.begin(mac,ip,dnsip,gateway,subnet);
	//display relevant information : serial
	
	displayInfo();

}
//diplays info about ethernet settings
void wiznet::displayInfo(void)
{
	Serial.print("MAC : ");	serialPrintMAC(mac);
	Serial.print("IP : ");	Serial.println(Ethernet.localIP());
	Serial.print("DNS : ");	Serial.println(Ethernet.dnsServerIP());
	Serial.print("GATEWAY : ");	Serial.println(Ethernet.gatewayIP());
	Serial.print("SUBNET : ");	Serial.println(Ethernet.subnetMask());
}
//prints mac address
void wiznet::serialPrintMAC(byte mac[6])
{
	for(char i=0;i<5;i++)
	{
		Serial.print(mac[i],HEX);
		Serial.print(":");
	}
	Serial.println(mac[5],HEX);
}

//setter function: sets server ( can be ommited at cost of making it public)
void wiznet::setServer(IPAddress& s)
{
	server=s;
}
//getter function
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
//waits till connect : 
//INPUT : timeout for the function in seconds
//RETURN : true on success / false on failure
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
//Startup routine 
//waits for checking till connect
//INPUT : timeout in seconds
//RETURN : true on setting startup settings/false else
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
	while(	(millis()-time) < timeoutSeconds*1000	)			//only check until timeout
	{
		res=client.connect( server,port);		//start TCP connection to server on Port
		if(res==1)
		{
			//send request to client
			client.print("GET /cas/startup.php?DEVID=");client.print(dev.getDeviceId());client.println(" HTTP/1.1");
			client.print("Host: ");client.println(server);
			client.println("Connection: Close");		//connection to keep close
			client.println();
			while(client.connected() )
			{
				if(client.available())
				{
					/*client.readBytesUntil(0x00,response,1024);*/
					response=client.readString();
					/*Serial.println("=-=-=-=-=-=-=-=-=-");
					Serial.println(response);
					Serial.println("-=-=-=-=-=-=-=-=-=");*/
					//response="NULL";
				}
			}
			
			break;
		}
	}
	client.stop();			// end the TCP connection
	setStartupSettings();	//set startup settings
	if(res==1)return true;	//function succeded in connnecting before  timeout
	else return false;		//function failed to connect before timeout

}

// sets startup settings 
//  sets startup settings :
// Device  ID, Method ,LCD Text, DateTime
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
}
// checks Data over the server

//input : (all string)
//method : <type of method> //currently for method check
//type : <type of ID> //RFID/FINGERPRINT
//uid : <User ID> 
//devid : <Device ID>
//time : <HHMMSS> //formatted time
//date : <DDMMYY> //formatted date
//lat : <lattitude>
//lon : <longitude>
//return 1 on success/ -1 on communication failure
int wiznet::checkData(String method,String type,String uid,String devid, String time,String date,String lat,String lon)
{
	String data;
	
	if(client.connect(server,port))
	{
		//if connected
		//send get request with all 
		data="METHOD="+method+"&TYPE="+type+"&UID="+uid+"&DEVID="+devid+"&TIME="+time+"&DATE="+date+"&LAT="+lat+"&LON="+lon;
		
		
		client.print(F("GET /cas/check.php?"));
		//client.print(F("GET /check.php?"));;
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
				String temp;
				while(1)
				{
					temp=client.readStringUntil('\r');
					if(temp.length()==1 && temp.charAt(0)=='\n')break;
				}
				response=client.readString();
				//client.readBytesUntil('\r',response,1024);
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

//processes the received data in the response buffer 
//checks for the specific response (eg id_found/ id_not_found)
//returns	 0 if id not found
//			 1 if id found
//		else -1 for error
int  wiznet::processData()
{
	int res;
	Serial.println(F("######################"));
	Serial.println(response);
	//int res = response.indexOf(F("id_"));
	//char * loc=strstr(response,"NOT FOUND");
	Serial.println(freeMemory(),DEC);
	
	//check for the occurance of string
	if(response.indexOf("id_not_found")>=0)
	{
		res= 0;
	}
	else if(response.indexOf("id_found")>=0)
	{
		res= 1;
	}
	else 
	{
		res=-1;
	}
		return res;
	
}

#endif