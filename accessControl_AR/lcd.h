/*
 * lcd.h
 *
 * Created: 08-05-2015 04:01:22 PM
 *  Author: Ajinkya
 */ 


#ifndef LCD_H_
#define LCD_H_
#include <LiquidCrystal.h>
#include "time.h"


class LCD:public LiquidCrystal
{
	public:
		LCD(uint8_t rs, uint8_t rw, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3):LiquidCrystal(rs,rw,enable,d0,d1,d2,d3){};
		void displayDateTime(RTCDateTime dateTime);
		void displayDateTime(void);
		
	
	};

#endif /* LCD_H_ */