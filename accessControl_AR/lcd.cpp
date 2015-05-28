/*
 * lcd.cpp
 *
 * Created: 08-05-2015 04:00:54 PM
 *  Author: Ajinkya
 */ 
#ifndef LCD_CPP
#define LCD_CPP

#include "lcd.h"

//reference to RTC object  clock (defined in main program  (.ino) file)
extern DS1307 clock;

//display date,time,default text on LCD
void LCD::displayDateTime()
{
	clear();
	displayDateTime(clock.getDateTime());
}

//helper function for displaying date, time, text on lcd
//INPUT : object from RTCDateTime dateTime containing current date and time
void LCD::displayDateTime(RTCDateTime dateTime)
{
	
	setCursor(0,0);	
	String date=String(dateTime.day)+"/"+String(dateTime.month)+"/"+String(dateTime.year%100);
	print(date);
	setCursor(8,0);
	String time=String(dateTime.hour)+":"+String(dateTime.minute)+":"+String(dateTime.second);
	print(time);
	
	// also display lcd default text
	
	setCursor(1,1);
	print(dev.getLcdDefaultText());
}
#endif