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
#include "string.h"
#include "stdlib.h"
struct uid;
extern  EthernetClient client;
class wiznet{
	
	IPAddress server;
	unsigned int port;
	//String response;
	char response[1024];
	
	public:
		
		bool init();
		bool startup(unsigned int timeoutSeconds);
		bool checkWaitConnect(unsigned int timeoutSeconds);
		void serialPrintMAC(byte mac[6]);
		void displayInfo(void);
		void setServer(IPAddress &s);
		IPAddress getServer(void);
		void setPort(unsigned int p);
		unsigned int getPort(void);
		int processData();
		
		/*following  sets the startup settings from the server's response*/
		
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
		
		int checkData(	uint8_t method /*CHECK/REGISTER*/,
						uid& userid,
						uint16_t devid, /*DEVICE ID*/
						uint32_t time,	/*TIME<HHMMSS> */
						uint32_t date,	/*DATE<DDMMYY>*/
						uint32_t lat,		/*LATTITUDE*/
						uint32_t lon		/*LONGITUDE*/
						);
		
		int checkData(	String method /*CHECK/REGISTER*/,
						String type /*RFID/FINGERPRINT*/,
						String uid, /*USER ID FOR <TYPE>*/
						String devid, /*DEVICE ID*/
						String time,	/*TIME<HH:MM:SS>*/
						String date,	/*DATE<DD:MM:YY>*/
						String lat,		/*LATTITUDE<String>*/
						String lon		/*LONGITUDE<String>*/
						);
		
		//one more function to send stored data
};



#endif /* WIZNET_H_ */