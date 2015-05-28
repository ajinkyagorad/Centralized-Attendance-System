/*
 * fingerprint.cpp
 *
 * Created: 23-05-2015 05:49:29 AM
 *  Author: Ajinkya
 */ 
#ifndef FINGERPRINT_CPP_
#define FINGERPRINT_CPP_
#include "fingerprint.h"

// 
//get fingerprint registerd ID
//INPUT : referenced uid 'userid'
//RESULT : userid Modified according to ID and validness

void fingerPrintClass::_getID(uid & userid)
{
		Serial1.begin(57600);		//begin serial connection
		Serial1.setTimeout(50);		//set timeout for reading
		userid.isValid=false;
		userid.type="FINGERPRINT";	//set type of ID in userid
		uint8_t p = getImage();		//get Image on fingerprint sensor
		//Serial.println("getImage");	
		if (p != FINGERPRINT_OK)  return ;
		p = image2Tz();				
		//Serial.println("image2Tz");
		if (p != FINGERPRINT_OK)  return ;
		p = fingerFastSearch();	
		//Serial.println("fingerFastSearch");
		if (p != FINGERPRINT_OK) 
		{ 
			userid.id="NULL";
			return ;
		}
		Serial.print(F("Finger ID"));		//comment if not required
		Serial.println(fingerID);			//comment if not required
		userid.id="ID"+String(fingerID);
		userid.isValid=true;				//set validness of data to true
		
		
		
}
//checks the init of sensor
//RETURN : true on initialization/ false otherwise
bool fingerPrintClass::checkSensor(void)
{
	return init();							//initialise the sensor
}

//initialize the sensor
//RETURN : true on initialization/ false otherwise
bool fingerPrintClass::init(void)
{
	begin(57600);
	return verifyPassword();
}


#endif /* FINGERPRINT_CPP_ */
