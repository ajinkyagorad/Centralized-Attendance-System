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
	//null constructor
}
//INPUT : _pinType  -- pin number of deciding type of sensor
idClass::idClass(int _pinType)
{
	pinType=_pinType;
}
//automatically set the type
//checks the PIN with pinType and depending
//on whether the pin is high or low  
//decides the sensor connected
//		--> HIGH => RFID
//		--> LOW  => FINGERPRINT
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
//initialize respective  sensor
//OUTPUT : true on success /false on failure
bool idClass::init(void)
{
	checkGetType();
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

//get id <UID> with  type
//INPUT : referenced uid _id
//RESULT : modified uid with respective parameters
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

//getter for idType
//RETURN : idType
String idClass::getType()
{
	return idType;
}
#endif /* ID_CPP_ */