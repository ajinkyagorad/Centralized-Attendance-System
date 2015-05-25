/*
 * buzzer.h
 *
 * Created: 16-05-2015 04:58:18 PM
 *  Author: Ajinkya
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_
#include "Arduino.h"
class buzzer{
	int pin;
	public:
		buzzer(int p);
		void registered(void);
		void notRegistered(void);
		void communicationError(void);
		void swipe(void);
	};



#endif /* BUZZER_H_ */