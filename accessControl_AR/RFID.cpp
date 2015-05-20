/*
 * RFID.cpp
 *
 * Created: 08-05-2015 05:59:03 AM
 *  Author: Ajinkya
 */ 

#ifndef  RFID_CPP_
#define  RFID_CPP_


#include "RFID.h"

bool RFID::init(void)
{
	
	return true;	//no initialisation sequence for RFID
	
}

bool RFID::getID(id& rfid)
{
	Serial1.begin(9600);
	Serial1.setTimeout(20);	//set  delay between timeout
	int bytesRead=Serial1.readBytes(rfid.buf,12);
	rfid.buf[13]=0;	//append 0 for string
	
	if(bytesRead==12)
	{
		rfid.isValid=true;
		Serial.println("****************");
		Serial.println("RFID: ");
		Serial.print("\tBytes Read : ");Serial.println(bytesRead);
		Serial.print("\tID : ");Serial.println(rfid.buf);
		Serial.println("****************");
		return true;
	}
	else
	{
		rfid.isValid=false;
		//Serial.println("rfid Read Timeout");
		return false;
	}
	
}


#endif