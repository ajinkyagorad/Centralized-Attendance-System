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
	
	userid.type=F("FINGERPRINT");
	
	Serial1.begin(9600);
	
	Serial1.setTimeout(100);
	{
		userid.id=Serial1.readStringUntil('*');
	}
	if(userid.id.indexOf("ID")>=0)
	{
		Serial.println("*****");
		Serial.println(userid.id);
		Serial.println("*****");
		userid.isValid=true;
	}
	else
	{
		userid.isValid=false;
	}
	
	
	
	
}
bool fingerPrintClass::init(void)
{
	begin(9600);

}


#endif /* FINGERPRINT_CPP_ */
