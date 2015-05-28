/*
 * RFID.cpp
 *
 * Created: 08-05-2015 05:59:03 AM
 *  Author: Ajinkya
 */ 

#ifndef  RFID_CPP_
#define  RFID_CPP_


#include "RFID.h"

//initialization for rfid -> currently none
//RETURNS : TRUE
bool RFIDClass::init(void)
{
	
	return true;	//no initialisation sequence for RFID
	
}
//get rfid  ID
//INPUT : referenced uid 'userid'
//RESULT : userid Modified according to ID and validness
void RFIDClass::_getID(uid& rfid)
{
	
	rfid.type="RFID";
	Serial1.begin(9600);
	Serial1.setTimeout(100);	//set  delay between timeout
// 	int bytesRead=Serial1.readBytes(rfid.buf,12);
// 	rfid.buf[13]=0;	//append 0 for string
	rfid.id=Serial1.readString();
	if(rfid.id.length()==12)			// rfid outputs 12 byte long id -> stored in string => valid data
	{
		rfid.isValid=true;
		
		//start up debug
		Serial.println("****************");
		Serial.println("RFID: ");
		
		
		Serial.print("\tBytes Read : ");Serial.println(rfid.id.length());
		Serial.print("\tID : ");Serial.println(rfid.id);
		Serial.println("****************");
		
		//end of debug
		rfid.isValid=true;		//set the validness of data, data is valid
	}
	else{
		rfid.isValid=false;		//if data length is not 12 then make it false
	}
	
	Serial1.end();
	
}


#endif