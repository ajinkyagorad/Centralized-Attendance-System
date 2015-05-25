/*
 * RGBled.cpp
 *
 * Created: 16-05-2015 09:38:44 PM
 *  Author: Ajinkya
 */ 
#ifndef RGBLED_CPP_
#define RGBLED_CPP_
#include "RGBled.h"
RGBLED::RGBLED(int pinR,int pinG,int pinB)
{
	pinRed=pinR;
	pinGreen=pinG;
	pinBlue=pinB;
	pinMode(pinRed,OUTPUT);
	pinMode(pinGreen,OUTPUT);
	pinMode(pinBlue,OUTPUT);
	
}
void RGBLED::set(int   r, int g, int b)
{
	analogWrite(pinRed,r);
	analogWrite(pinGreen,g);
	analogWrite(pinBlue,b);
}
void RGBLED::set(bool r,bool g,bool b)
{
	if(r)digitalWrite(pinRed,HIGH);
	else digitalWrite(pinRed,LOW);
	if(g)digitalWrite(pinGreen,HIGH);
	else digitalWrite(pinGreen,LOW);
	if(b)digitalWrite(pinBlue,HIGH);
	else digitalWrite(pinBlue,LOW);
}
void RGBLED::registered()
{
	set(false,true,false);
}
void RGBLED::notRegistered()
{
	set(true,false,false);
}
void RGBLED::communicationError()
{
	set(false,false,true);
}
void RGBLED::clear()
{
	set(false,false,false);
}
void RGBLED::connecting()
{
	set(255,255,255);
}
#endif /* RGBLED_CPP_ */