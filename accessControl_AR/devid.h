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
struct devStatus
{
	String deviceMethod;
	String lcdDefaultText;
	String	devid;
	};
class devClass{
	devStatus status;
	public:
		//set the device id : 
		//device id is string of length 4
		//address  0to 5 is used for storing  unique id
		// as ID1234 of type string
		//also 6th position for string is used
		void setDeviceId(String id);
		String getDeviceId(void);
		void  deleteID(void);
	
		void setDeviceMethod(String method);
		String getDeviceMethod();

		void setLcdDefaultText(String str);
		String getLcdDefaultText();
		
		void printDevStatus(void);

};

extern devClass dev;
#endif /* DEVID_H_ */