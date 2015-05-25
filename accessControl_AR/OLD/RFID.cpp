/*
 * RFID.cpp
 *
 * Created: 08-05-2015 05:59:03 AM
 *  Author: Ajinkya
 */ 

#ifndef  RFID_CPP_
#define  RFID_CPP_


#include "RFID.h"

bool RFIDClass::init(void)
{
	
	return true;	//no initialisation sequence for RFID
	
}

void RFIDClass::_getID(uid& rfid)
{
	
	rfid.type='R';
	Serial1.begin(9600);
	Serial1.setTimeout(20);	//set  delay between timeout
// 	int bytesRead=Serial1.readBytes(rfid.buf,12);
// 	rfid.buf[13]=0;	//append 0 for string
	//rfid.id=Serial1.readString();
	uint8_t bytesRead=Serial.readBytes(rfid.id,12);
	rfid.id[13]=0;
	if(bytesRead==12)
	{
		rfid.isValid=true;
		Serial.println(F("****************"));
		Serial.println(F("RFID: "));
		Serial.print(F("\tBytes Read : "));Serial.println(bytesRead,DEC);
		Serial.print(F("\tID : "));Serial.println(rfid.id);
		Serial.println(F("****************"));
		rfid.isValid=true;
	}
	else{
		rfid.isValid=false;
	}
	
	
	
}


#endif