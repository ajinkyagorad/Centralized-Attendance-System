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
	
	
	digitalWrite(pinType,LOW);
	pinMode(pinType,INPUT);
	int state=digitalRead(pinType);
	
	if(state==LOW/*idType==F("RFID")*/)
	{
		rfid._getID(_id);
		

	}
	else if (state ==HIGH/*idType==F("FINGERPRINT")*/)
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