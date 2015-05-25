/*
 * time.h
 *
 * Created: 16-05-2015 02:10:40 PM
 *  Author: Ajinkya
 */ 


#ifndef TIME_H_
#define TIME_H_
#include <DS1307.h>
extern DS1307 clock;
class timeClass{
	public:
		void setDateTime_YmdHis(String fDateTime);
		void getDateTimeStr(String& date, String& time);
		void getDateTimeStr(char* date,char* time);
};

extern timeClass timeManage;
#endif /* TIME_H_ */