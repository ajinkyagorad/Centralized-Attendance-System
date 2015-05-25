/*
 * RFID.h
 *
 * Created: 08-05-2015 05:58:32 AM
 *  Author: Ajinkya
 */ 

#include <arduino.h>
#ifndef RFID_H_
#define RFID_H_
#include "id.h"
//uses Serial1
struct uid;
class RFIDClass{
	
	public:
		bool init(void);
		void _getID(uid& rfid);
	
};




#endif /* RFID_H_ */