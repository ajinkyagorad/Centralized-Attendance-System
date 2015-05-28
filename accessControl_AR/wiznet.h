/*
 * wiznet.h
 *
 * Created: 08-05-2015 03:00:20 PM
 *  Author: Ajinkya
 */ 


#ifndef WIZNET_H_
#define WIZNET_H_

#include <Ethernet.h>
#include "devid.h"
#include "time.h"

//object for client
extern  EthernetClient client;

class wiznet{
	
	IPAddress server;	//IP address server 	
	unsigned int port;	//port of the server
	String response;	// to store the response from the server <NOTE : use buffer for memory constraints>// dynamic memalloc,,server to ensure
	//char response[1024];
	
	public:
		//initialise the ethernet
		bool init();
		//startup routine
		bool startup(unsigned int timeoutSeconds);
		// waits till connect
		bool checkWaitConnect(unsigned int timeoutSeconds);
		//debug :print mac
		void serialPrintMAC(byte mac[6]);
		//debug : print  info
		void displayInfo(void);
		//set server
		void setServer(IPAddress &s);
		//get server
		IPAddress getServer(void);
		//set Port
		void setPort(unsigned int p);
		//get port
		unsigned int getPort(void);
		//process data
		int processData();
		
		/*following  sets the startup settings from the server's response*/
		void setStartupSettings();
		/*
		int checkData
		String method	CHECK/REGISTER
		String type		RFID/FINGERPRINT
		String uid,		USER ID FOR <TYPE>
		String devid,	DEVICE ID
		String time,	TIME<HH:MM:SS>
		String date,	DATE<DD:MM:YY>
		String lat,		LATTITUDE<String>
		String lon		LONGITUDE<String>
		send data and look for response
		data sent in GET format
		sends formatted http get header and processes the response accordingly
		response after header in String response (only one line)
		0 indicate failure with non qualified error ;
		 -ve might indicate specific error;
		1 or any positive indicate success with valid data in buffer
		
		specific to some -ve errors:
		-1 = connection problem 
		
		
		
		*/
		int checkData(	String method /*CHECK/REGISTER*/,
						String type /*RFID/FINGERPRINT*/,
						String uid, /*USER ID FOR <TYPE>*/
						String devid, /*DEVICE ID*/
						String time,	/*TIME<HH:MM:SS>*/
						String date,	/*DATE<DD:MM:YY>*/
						String lat,		/*LATTITUDE<String>*/
						String lon		/*LONGITUDE<String>*/
						);
		
		
};



#endif /* WIZNET_H_ */