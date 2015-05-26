/*
 * fingerprint.cpp
 *
 * Created: 23-05-2015 05:49:29 AM
 *  Author: Ajinkya
 */ 
#ifndef FINGERPRINT_CPP_
#define FINGERPRINT_CPP_
#include "fingerprint.h"



void fingerPrintClass::_getID(uid & userid)
{
		Serial1.begin(57600);
		Serial1.setTimeout(50);
		userid.isValid=false;
		userid.type="FINGERPRINT";
		uint8_t p = getImage();Serial.println("getImage");
		if (p != FINGERPRINT_OK)  return ;
		p = image2Tz();			Serial.println("image2Tz");
		if (p != FINGERPRINT_OK)  return ;
		p = fingerFastSearch();	Serial.println("fingerFastSearch");
		if (p != FINGERPRINT_OK) 
		{ 
			userid.id="NULL";
			return ;
		}
		Serial.print(F("Finger ID"));
		Serial.println(fingerID);
		userid.id="ID"+String(fingerID);
		userid.isValid=true;
		
		
		
}
	
bool fingerPrintClass::checkSensor(void)
{
	return init();
}

bool fingerPrintClass::init(void)
{
	begin(57600);
	return verifyPassword();
}


#endif /* FINGERPRINT_CPP_ */
