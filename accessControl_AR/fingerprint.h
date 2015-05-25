/*
 * fingerprint.h
 *
 * Created: 23-05-2015 05:49:49 AM
 *  Author: Ajinkya
 */ 


#ifndef FINGERPRINT_H_
#define FINGERPRINT_H_
#include "Arduino.h"
#include <Adafruit_Fingerprint.h>
#include "id.h"

struct uid;

class fingerPrintClass:public Adafruit_Fingerprint{
	
	public:
		//fingerPrintClass(void);
		//fingerPrintClass(void);
		fingerPrintClass(HardwareSerial& hws):Adafruit_Fingerprint(&hws){}
		bool init(void);
		//enrolls /adds the user and returns the user id
		uid enroll(void);
		//removes the user based on uid provided
		//bool remove(int id);
		bool remove(uid id);
		//returns the user id
		void _getID(uid& userid);
	};


#endif /* FINGERPRINT_H_ */