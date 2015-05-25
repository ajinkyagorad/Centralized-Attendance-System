/*
 * id.h
 *
 * Created: 23-05-2015 07:24:20 AM
 *  Author: Ajinkya
 */ 


#ifndef ID_H_
#define ID_H_
#include "Arduino.h"
#include "RFID.h"
#include "fingerprint.h"


class fingerPrintClass;
extern fingerPrintClass finger;

class RFIDClass;
extern RFIDClass rfid;

struct uid
{
	String id;
	String type;
	bool isValid;
};


class idClass{
	
	String idType;
	int pinType;
	public:
		idClass();
		bool init(String _type);
		void getID(uid& _id);
	//	uid enroll(void);
	//	bool remove(uid);
		void setType(String _type);
		String getType(void);
	};
	



#endif /* ID_H_ */