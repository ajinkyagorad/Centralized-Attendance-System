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
	
	rfid.type="RFID";
	Serial1.begin(9600);
	Serial1.setTimeout(50);	//set  delay between timeout
// 	int bytesRead=Serial1.readBytes(rfid.buf,12);
// 	rfid.buf[13]=0;	//append 0 for string
	rfid.id=Serial1.readString();
	if(rfid.id.length()==12)
	{
		rfid.isValid=true;
		Serial.println("****************");
		Serial.println("RFID: ");
		Serial.print("\tBytes Read : ");Serial.println(rfid.id.length());
		Serial.print("\tID : ");Serial.println(rfid.id);
		Serial.println("****************");
		rfid.isValid=true;
	}
	else{
		rfid.isValid=false;
	}
	
	Serial1.end();
	
}


#endif