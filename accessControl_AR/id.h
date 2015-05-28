/*
 * id.h
 *
 * Created: 23-05-2015 07:24:20 AM
 *  Author: Ajinkya
 */ 


#ifndef ID_H_
#define ID_H_
//include files
#include "Arduino.h"
#include "RFID.h"
#include "fingerprint.h"

//reference to external class objects
class fingerPrintClass;
extern fingerPrintClass finger;

class RFIDClass;
extern RFIDClass rfid;
//structure for storeing UID
//	contains :
//	->id <string>		-- stores the id  (eg '18008DD45918','ID5';)
//	->type <string>		-- stores the type ( must be 'RFID' or 'FINGERPRINT')
//	->validFlag <bool>	-- stores the validity of data (boolean value)
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
		//default constructor
		idClass();
		//intialization constructor
		idClass(int _pinType);
		// initialise respective  sensor
		bool init(void);
		//get ID
		void getID(uid& _id);
	//	uid enroll(void);
	//	bool remove(uid);
	
		//get type of sensor
		String getType(void);
		
		//automatically get type of sensor depending on state of pin
		void checkGetType(void);
	};
	



#endif /* ID_H_ */