/*
 * buzzer.cpp
 *
 * Created: 16-05-2015 04:58:11 PM
 *  Author: Ajinkya
 */ 

#ifndef BUZZER_CPP_
#define BUZZER_CPP_
#include "buzzer.h"
buzzer::buzzer(int p)
{
	pin=p;
}

void buzzer::communicationError()
{
	tone(pin,1000,1000);
	
}
void buzzer::registered()
{
	tone(pin,4000);
	delay(300);
	tone(pin,2000);
	delay(300);
	tone(pin,4000,200);
	
}
void buzzer::notRegistered()
{
	tone(pin,200);
	delay(200);
	tone(pin,4000);
	delay(200);
	tone(pin,2000);
	delay(200);
	tone(pin,4000);
	delay(200);
	tone(pin,1000);
	delay(200);
	tone(pin,4000);
	delay(200);
	tone(pin,2000);
	delay(200);
	tone(pin,4000,200);
	
	
}
void buzzer::swipe()
{
	tone(pin,4000,800);
}

#endif /* BUZZER_CPP_ */
