/*
 * RGBled.h
 *
 * Created: 16-05-2015 09:38:53 PM
 *  Author: Ajinkya
 */ 


#ifndef RGBLED_H_
#define RGBLED_H_
#include "Arduino.h"
class RGBLED {
		int pinRed,pinGreen,pinBlue;
	public:
		RGBLED(int pinR,int pinG,int pinB);
		void set(int r, int g, int b);
		void set(bool r,bool g,bool b);
		void registered(void);
		void notRegistered(void);
		void communicationError(void);
		void clear(void);
		void connecting(void);
	};



#endif /* RGBLED_H_ */