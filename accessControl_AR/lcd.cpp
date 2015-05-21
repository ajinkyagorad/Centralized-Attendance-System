/*
 * lcd.cpp
 *
 * Created: 08-05-2015 04:00:54 PM
 *  Author: Ajinkya
 */ 
#ifndef LCD_CPP
#define LCD_CPP
#include "lcd.h"

extern DS1307 clock;
void LCD::displayDateTime()
{
	clear();
	displayDateTime(clock.getDateTime());
}
void LCD::displayDateTime(RTCDateTime dateTime)
{
	
	setCursor(0,0);	
	String date=String(dateTime.day)+"/"+String(dateTime.month)+"/"+String(dateTime.year%100);
	print(date);
	setCursor(8,0);
	String time=String(dateTime.hour)+":"+String(dateTime.minute)+":"+String(dateTime.second);
	print(time);
}
#endif