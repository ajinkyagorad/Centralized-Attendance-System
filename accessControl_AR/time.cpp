/*
 * time.cpp
 *
 * Created: 16-05-2015 02:10:16 PM
 *  Author: Ajinkya
 */ 
#ifndef TIME_CPP_
#define TIME_CPP_
#include "time.h"

void timeClass::setDateTime_YmdHis(String fDateTime)
{
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	
	year=fDateTime.substring(0,4).toInt();
	month=fDateTime.substring(4,6).toInt();
	day=fDateTime.substring(6,8).toInt();
	hour=fDateTime.substring(8,10).toInt();
	minute=fDateTime.substring(10,12).toInt();
	second=fDateTime.substring(12,14).toInt();
	
	
	clock.setDateTime(year,month,day,hour,minute,second);
	Serial.println("!Date & Time Set");
}
#endif