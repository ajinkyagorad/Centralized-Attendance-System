/*
 * devid.cpp
 *
 * Created: 20-05-2015 10:01:41 PM
 *  Author: Ajinkya
 */ 

#ifndef DEVID_CPP_
#define DEVID_CPP_
#include "devid.h"


//id stored on first 2 location address 0x0000 and 0x0001
//HIGH byte at 0x0000
//LOW byte at 0x0001
// both form the device id
void devClass::setDeviceId(uint16_t id)
{
	EEPROM.write(0,id>>8);	//write upper byte
	EEPROM.write(1,id);	//write lower byte
	
}

uint16_t devClass::getDeviceId(void)
{
	uint16_t id=0;
	id=EEPROM.read(0);		//get upper byte
	id=id<<8;				//move  it to upper byte from lower byte
	id|=EEPROM.read(1);		//get lower byte
}
void  devClass::deleteDeviceID(void)
{
	
	EEPROM.write(0,0xFF);		
	EEPROM.write(1,0XFF);
}

#endif /* DEVID_CPP_ */