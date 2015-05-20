/*
 * RFID.h
 *
 * Created: 08-05-2015 05:58:32 AM
 *  Author: Ajinkya
 */ 

#include <arduino.h>
#ifndef RFID_H_
#define RFID_H_
//uses Serial1
namespace RFID{
	struct id{
		char buf[13];
		bool isValid;
		};
	bool init(void);
	bool getID(id& rfid);
	
};




#endif /* RFID_H_ */