/*
 * GPS_NMEA.h
 *
 * Created: 22-05-2015 11:21:21 PM
 *  Author: Ajinkya
 */ 


#ifndef GPS_NMEA_H_
#define GPS_NMEA_H_
#include "Arduino.h"
struct position
{
	String lat;
	String lon;
	bool isValid;
	};
class GPSClass {
	position lastPosition;
	public:
		//getLattitude and Longitude
		GPSClass();
		bool init(void);
		void getLatLon(position & pos, unsigned long timeout_ms=2000);
		bool update(unsigned long timeout_ms);
		void getLastLatLon(position pos);
		
	};



#endif /* GPS_NMEA_H_ */