/*
 * memory.h
 *
 * Created: 11-05-2015 10:44:12 PM
 *  Author: Ajinkya
 */ 


#ifndef MEMORY_H_
#define MEMORY_H_

//#include <SD.h>
#ifndef SDrelease()	
#define SDrelease()	digitalWrite(4,HIGH)
#endif
#ifndef ETrelease()	
#define ETrelease()	digitalWrite(10,HIGH)
#endif
//all masking functions here
class memory{
		int chipSelectPin;
	public:
		memory(void);
		memory(int csPin);
		bool init();
		/*save the data  in case of communication failure*/
		void saveData(String data);
	};
#endif /* MEMORY_H_ */