/*
 * devid.h
 *
 * Created: 20-05-2015 10:01:35 PM
 *  Author: Ajinkya
 */ 


#ifndef DEVID_H_
#define DEVID_H_
#include "Arduino.h"
#include  <EEPROM/EEPROM.h>
/************definations****/
#define rled    5
#define gled    6
#define bled    7
#define buzzpin 11
#define method_check  0
#define method_add    1
#define method_delete 2
/*****************************/

class devClass{
	
	
	public:
		uint8_t deviceMethod;
		uint16_t	devid;
		void  deleteID(void);
		void setDeviceId(uint16_t id);
		uint16_t getDeviceId(void);
		void  deleteDeviceID(void);	
};

extern devClass dev;
#endif /* DEVID_H_ */