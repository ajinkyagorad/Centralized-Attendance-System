/*
 * GPS_NMEA.h
 *
 * Created: 22-05-2015 11:21:21 PM
 *  Author: Ajinkya
 */ 


#ifndef GPS_NMEA_H_
#define GPS_NMEA_H_
#include "Arduino.h"

//uses  Serial3
//supports the GPS sensors with NMEA sequence output with serial
// default baud rate of serial 9600

// position object
// stores the postition (lat/lon)
// -> lattitude <string>
// -> longitude <string>
// -> valid flag <bool>
struct position
{
	String lat;
	String lon;
	bool isValid;
	};
	
// GPS device function wrapper class
class GPSClass {
	position lastPosition;	//variable for storing  the last updated position
	public:
		GPSClass();				//default constructor
		bool init(void);		//initialize the sensor
		void getLatLon(position & pos, unsigned long timeout_ms=200);	// get  lattitude and longitude within timeout :default (200 ms )						
		bool update(unsigned long timeout_ms);							//update  the position within timeout
		void getLastLatLon(position& pos);								// get last updated position
		
	};



#endif /* GPS_NMEA_H_ */