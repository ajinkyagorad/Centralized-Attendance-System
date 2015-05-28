/*
 * RGBled.h
 *
 * Created: 16-05-2015 09:38:53 PM
 *  Author: Ajinkya
 */ 


#ifndef RGBLED_H_
#define RGBLED_H_
#include "Arduino.h"

// function wrapper class for RGB led
class RGBLED {
		int pinRed,pinGreen,pinBlue;	//pins for red, green, blue.
	public:
		RGBLED(int pinR,int pinG,int pinB);		//constructor for initializing pins for red, green blue	
		void set(int r, int g, int b);			// set values for rgb using PWM
		void set(bool r,bool g,bool b);			// set high/ low for RGB
		void registered(void);					//led color on registered
		void notRegistered(void);				//led color on not registered
		void communicationError(void);			//led color on communication error
		void clear(void);						//clear the led's set all low
		void connecting(void);					//led color for connecting
	};



#endif /* RGBLED_H_ */