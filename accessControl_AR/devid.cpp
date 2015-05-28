/*
 * devid.cpp
 *
 * Created: 20-05-2015 10:01:41 PM
 *  Author: Ajinkya
 */ 

#ifndef DEVID_CPP_
#define DEVID_CPP_
#include "devid.h"


/*following  writes IDXXXX to location  0 on EEPROM on mcu*/
void devClass::setDeviceId(String id)
{
	String data="ID"+id;
	deleteID();
	for(int i = 0;i<6;i++)
	{
		EEPROM.write(i,data.charAt(i));
	}
	EEPROM.write(6,0x00);
	
}
//get device id from EEPROM
//OUTPUT : string with device id stored on eeprom
String devClass::getDeviceId(void)
{
	String data="XXXXXX";
	
	for(int i=0;i<6;i++)	
	{
		data.setCharAt(i,EEPROM.read(i));
	}
	
	
	if(data.indexOf("ID")==0)			//to check, id is always stored with IDXXXX
	{
		//true : valid string
		return data.substring(2,6);		//return only the numberstring
	}
	else
	{
		// not saved
		return "0000";		//return  default value
	}
}

//deletes the id from the EEPROM
//clears the region of EEPROM where id is residing
void  devClass::deleteID(void)
{
	for(int i=0;i<=6;i++)		//also include null character
	EEPROM.write(i,0xFF);		//delete  all data from 0 to 6 => 7 cycles
}

//following are setter and getter functions for device method and lcd default text
//**//
void devClass::setDeviceMethod(String method)
{
	status.deviceMethod=method;
}
String devClass::getDeviceMethod()
{
	return status.deviceMethod;
}
void devClass::setLcdDefaultText(String str)
{
	status.lcdDefaultText=str;
}
String devClass::getLcdDefaultText()
{
	return  status.lcdDefaultText;
}

//**//

//prints device status to serial monitor
//debugging purpose
void devClass::printDevStatus()
{
	Serial.println("!----Device Status------!");
	Serial.println("Method : "+status.deviceMethod);
	Serial.println("Device ID : "+status.devid);
	Serial.println("LCD Text: "+status.lcdDefaultText);
	Serial.println("!----End----------------!");
}
#endif /* DEVID_CPP_ */