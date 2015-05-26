/*
 * id.cpp
 *
 * Created: 23-05-2015 07:23:51 AM
 *  Author: Ajinkya
 */ 


#ifndef ID_CPP_
#define ID_CPP_

#include "id.h"


idClass::idClass()
{
	pinType=29;
}
void idClass::checkGetType(void)
{
	
		digitalWrite(pinType,LOW);
		pinMode(pinType,INPUT);
		int state=digitalRead(pinType);
		if(state==HIGH)
		{
			idType="RFID";
		}
		else 
		{
			idType="FINGERPRINT";
		}
}
bool idClass::init(String _type)
{
	setType(_type);
	bool isSuccessful=false;
	
	if(idType=="RFID")
	{
		// no initialisation sequence
		isSuccessful=true;
	}
	else if(idType=="FINGERPRINT")
	{
		//initialise it at baud rate of 57600
		isSuccessful=finger.init();
	}
	return isSuccessful;
}

void idClass::getID(uid&  _id)
{
	
	

	checkGetType();
	if(idType==F("RFID"))
	{
		rfid._getID(_id);
		

	}
	else if (idType==F("FINGERPRINT"))
	{
		 finger._getID(_id);
		
	}
	else
	{
		
	}
	
}

void idClass::setType(String _type)
{
	idType= _type;
}
String idClass::getType()
{
	return idType;
}
#endif /* ID_CPP_ */