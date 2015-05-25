#include <MemoryFree.h>
#include <Adafruit_Fingerprint.h>
#include <EEPROM.h>
#include <Wire.h>
//#include <SD.h>
//#include <GSM.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <Ethernet.h>
//#include <EthernetClient.h>
#include <DS1307.h>
/*
 * accessControl_AR.ino
 *
 * Created: 5/8/2015 5:20:20 AM
 * Author: Ajinkya

 */ 
#include "wiznet.h"
#include "time.h"
#include "lcd.h"
#include "RGBled.h"
#include "buzzer.h"
//#include "memory.h"
#include "devid.h"
//#include "GPS_NMEA.h"
#include "id.h"
#include "RFID.h"
#include "fingerprint.h"
/***********************/
LCD lcd(22,23,24,25,26,27,28);
wiznet ether;
EthernetClient client;
DS1307 clock;
RGBLED led(5,6,7);
buzzer buzz(8);
//memory disk(4);		//chip select  for sd card
timeClass timeManage;
devClass dev;
//GPSClass gps;
fingerPrintClass finger(Serial1);
idClass userID;
RFIDClass rfid;
/*******************************/
#ifndef SDrelease()
#define SDrelease()	digitalWrite(4,HIGH)
#endif
#ifndef ETrelease()
#define ETrelease()	digitalWrite(10,HIGH)
#endif
/*******************************************/
unsigned long timeServerCheck;
bool serverFailed;
//position location;
String MODE;
void setup()
{	 

		
	  /* add setup code here, setup code runs once when the processor starts */
	  pinMode(10,OUTPUT);	//for ethernet
	  pinMode(4,OUTPUT);	//for SD 
	  pinMode(53,OUTPUT);
	  Serial.begin(9600);
	  delay(200);
	  SDrelease();
	  if(userID.init("FINGERPRINT"))
	  {
		  Serial.println("Sensor FOUND");
	  }
	  else Serial.println("Sensor NOT FOUND");
	  Serial.print("free MEMEORY :");
	  Serial.println(freeMemory(),DEC);
	  ether.init();
	  //gps.init();
	  clock.begin();
	  lcd.begin(16,2);

	  lcd.print("initialised");
	  Serial.println("Initialised");
	  lcd.home();lcd.print("connecting...");
	  Serial.println("Waiting for connection..");
	  
	  
	  if(ether.checkWaitConnect(2))		//startup with timeout
	  {
		  Serial.print("**free MEMEORY :");
		  Serial.println(freeMemory(),DEC);
		  Serial.println("connected>>>");
		  lcd.home();lcd.print("Connected   ");
		 
		  serverFailed=false;
	  }
	  else 
	  {
		  Serial.print("**free MEMEORY :");
		  Serial.println(freeMemory(),DEC);
		  Serial.println("Error Connecting");
		  
		  lcd.home(); lcd.print("Error Connecting");
		  serverFailed=true;
		  //use default mode for checking
		  dev.deviceMethod=method_check;
	  }
	  
	  
	//  Serial.println("free Ram :"+freeMemory());
	  
	  
	   timeServerCheck=millis();
	  
}

uid userid;
void loop()
{
		
		
		
		Serial.print("**free MEMORY :");
		Serial.println(freeMemory(),DEC);
		SDrelease();
		userid.isValid=false;
		userID.getID(userid);	//instead a function to get any ID and type
	//	Serial.println("free Ram :"+freeMemory());
		gps.getLatLon(location);
		if(userid.isValid==true)	// if a valid id
		{
			buzz.swipe();		//beep buzzer for swipe/thumb successful impression
			
			//following  with ethernet
			//get date time
			
			//timeManage.getDateTimeStr(date,time);
			if(ether.checkData(dev.deviceMethod,userid,dev.devid,0,0,0,0)>0)	//function to send data for checking/ receiving and look for its response
			{
				//process received data
				//if data for checking : 
				//check if registered/not registered & do accordingly
				lcd.clear();
				lcd.setCursor(1,0);
				if(ether.processData()==1)		//funtion which checks the response and returns the specific value dependent on method and yes/no (if the method was finished or registerd/not registered)
				{
					
					lcd.print(" Registered :)");
					led.registered();
					buzz.registered();
					//respective code here	
					
				}
				else
				{
					lcd.print("Not Registered :(");
					led.notRegistered();
					buzz.notRegistered();
				}
					
			}
			else// in case the communication was not done  
			{
				//set serverFailed=true;		//to signify the error in transmission ;
				//store data on sd card;
				lcd.clear();
				lcd.home();
				lcd.print("Communication ");
				lcd.setCursor(1,1);
				lcd.print("Error");
				led.communicationError();
				buzz.communicationError();
				//disk.saveData(ether.getDataNotSent());	//save data on sd card
			}
			delay(1000);	// for beep and lcd persistence of message
		}
		else
		{
			lcd.clear();
			led.clear();
			
			lcd.displayDateTime();
		}
		
	/*	//try after every 60 seconds if the server is available and send data if 
		if(millis()-timeServerCheck>60000 && serverFailed)// if time from last was greater than 60sec and serverFailed to connect
		{
			timeServerCheck=millis();// save current time for next check
			/ *** CHECK  connection status
				 //if able to connect  
					// check and transmit any pending files
						//if all files transmitted
				// if not connect set serverFailed
				* /
		}*/
}
