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

//device status object
//contains
//	-> device method <string> --> stores the device method to use
//	-> lcd default text <string> -->stores the default lcd text to display
//	-> device id <string> --> stores the device id 
struct devStatus
{
	String deviceMethod;
	String lcdDefaultText;
	String	devid;
	};
// devClass for wrapper fuctions of device
class devClass{
	devStatus status;
	public:
		//set the device id : 
		//device id is string of length 4
		//address  0to 5 is used for storing  unique id
		// as ID1234 of type string
		//also 6th position for string is used
		
		void setDeviceId(String id);	//set device id in EEPROM
		String getDeviceId(void);		// get device id stored in EEPROM
		void  deleteID(void);			// delete clears space reservered for storing devID
	
		void setDeviceMethod(String method);	//set device method <not stored in EEPROM>
		String getDeviceMethod();				//get device method <not stored in EEPROM>
	
		void setLcdDefaultText(String str);		//set default lcd text
		String getLcdDefaultText();				// get default lcd text
		
		void printDevStatus(void);				//print device status it has

};

extern devClass dev;
#endif /* DEVID_H_ */