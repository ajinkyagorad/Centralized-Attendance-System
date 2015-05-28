
//include arduino library
//include as Project->Add/Import Sketch Library/..

/*to get teh free RAM available*/
#include <MemoryFree.h>		
/*Fingerprint sensor library from adafruit ( but slightly modified)*/
#include <Adafruit_Fingerprint.h>
/*EEPROM to store device id */
#include <EEPROM.h>
/*Wire library (I2C Protocol) for DS1307*/
#include <Wire.h>
/*SD card library for interfacing with SD card (SPI interface ),default chip select pin 4*/
#include <SD.h>
//!!*GSM library for sim 300: still not incorporated*/

/*LCD 16x2 interface library*/
#include <LiquidCrystal.h>
/*SPI library for Ethernet and SD card*/
#include <SPI.h>
/*Ethernet library  for interfacing with W5100 Wiznet chip (provide TCP IP support on chip)*/
#include <Ethernet.h>
/*Ethernet  Client library (for instance client)*/
#include <EthernetClient.h>
/*DS1307 Real time clock library*/
#include <DS1307.h>
////////////////////////////////////////////////////
/*
 * accessControl_AR.ino
 *
 * Created: 5/8/2015 5:20:20 AM
 * Author: Ajinkya
 * This file (accessControl_AR.ino) is a arduino project file 
 containing the main code for the whole procedure .
 * uses functions from arduino's library and some custom  defined file included below
 
 
 HardWare connections:
		UART :
			UART0 (Serial) -> reserved for debugging purposes
			UART1 (Serial1) ->RFID(EM-18 RFID Reader Module) / FINGERPRINT (R305 Fingerprint Sensor)
			UART2 (Serial2) ->Reserved for SIM300/ SIM900 GPS module
			UART3 (Serial3) ->GPS Receiver	(SIM28ML)
		SPI :
			( ATmega2560 has only one SPI port)shared between SD card and Ethernet  Wiznet Chip
			Chip Select 10 -> Wiznet ethernet chip
			Chip Select 4 -> SD card
			for more info http://www.arduino.cc/en/Main/ArduinoEthernetShield
		I2C :
			DS1307 RTC  (used Tiny RTC module // also contains 32kbit EEPROM <not used>)
		
		PINs :
			->22,23,24,25,26,27,28 defined for LCD below
			->5,6,7 defined for RGB led below
			->11 defined for buzzer below
			->29 defined for sensor select (dedicated for plug and play) defined below 'idClass'
		
 Software Requirements : (Windows 8.1 )
			-> Atmel Studio 6.0
			-> Visual Micro Plugin + Arduino 1.6.1 (other doesn't work at this time // later updated visual micro version )
			-> WAMP	PHP server (optional)
<!> all the lines with Serial.<> can be commented and must not affect the sequence of program</!>
 *NOTE:
	while+f using SD card:
		deselectEthernet ie make CS pin of EThernet high
	and while using ethernet 
		deselect SD card ie make CS pin of SD high
	MACROS:
		SDrelease() releases SD bus;
		ETrelease() releases ETh bus
 */ 
/////////////////////////////////////////////////////////////
/*W5100 chip function helping library*/
#include "wiznet.h"
/*provides time management*/
#include "time.h"
/*Extra LCD routines */
#include "lcd.h"
/*controls RGBLED*/
#include "RGBled.h"
/*controls buzzer*/
#include "buzzer.h"
/*contains helping routines for saving File in case of communication ERROR
File saved in SD card : not implemented*/
//#include "memory.h"
/*manages device method, id, and default  text on lcd*/
#include "devid.h"
/*decodes the standard NMEA sequence from GPS*/
#include "GPS_NMEA.h"
/*manages rfid and fingerprint plug and play compatibility*/
#include "id.h"
/*rfid library*/
#include "RFID.h" 
/*Fingerprint helper library*/
#include "fingerprint.h"
/////////////////////////////////////////////////////
/*lcd object with  pins rs,rw,e,d4,d5,d6,d7 in order*/
LCD lcd(22,23,24,25,26,27,28);			
/*Ethernet control object*/
wiznet ether;
/*instance of Ethernet client to handle connections*/
EthernetClient client;
/*RTC to get date and time*/
DS1307 clock;
/*RGB led with pins RED, GREEN, BLUE in order*/
RGBLED led(5,6,7);
/*buzzer control with pin connection to buzzer*/
buzzer buzz(11);
/*SD card manager  with chip select pin */
//memory disk(4);		//chip select  for sd card
/*managing time*/
timeClass timeManage;
/*device management*/
devClass dev;
/*GPS instance to get location*/
GPSClass gps;
/*finger print instance with Hardware Serial*/
fingerPrintClass finger(Serial1);
/*managing plug and play compatibility */
idClass userID(29);
/*rfid instance*/
RFIDClass rfid;
//////////////////////////////////////////////////////////
#ifndef SDrelease()
#define SDrelease()	digitalWrite(4,HIGH)
#endif
#ifndef ETrelease()
#define ETrelease()	digitalWrite(10,HIGH)
#endif
/////////////////////////global-var///////////////////////
//unsigned long timeServerCheck;			//to check for server if connected after certain amout of time
//bool serverFailed;						//to flag if connection to servers was not done 
position location;							// location containing latitude and longitude
uid userid;									// storing uid with type
//////////////////////////////////////////////////////////
/*one time setup*/
void setup()
{


	  /* add setup code here, setup code runs once when the processor starts */
	  pinMode(10,OUTPUT);	//for ethernet
	  pinMode(4,OUTPUT);	//for SD 
	  pinMode(53,OUTPUT);	// for spi to work ss pin must be output
	  Serial.begin(9600);	//initialsise serial for debugging
	  delay(200);			// delay so that all modules boot up
	  SDrelease();			
	  if(userID.init())		//check if the respective sensor is initialised (if requires ini sequence)
	  {
		  Serial.println("Sensor FOUND");
	  }
	  else Serial.println("Sensor NOT FOUND");
	  
	  Serial.print("free MEMEORY :");
	  Serial.println(freeMemory(),DEC);
	  ether.init();			//initialise ethernet
	  gps.init();			//initialise GPS
	  clock.begin();		// initialise DS1307
	  lcd.begin(16,2);		//initialise LCD
	
	  lcd.print("initialised");
	  Serial.println("Initialised");
	  lcd.home();lcd.print("connecting...");
	  Serial.println("Waiting for connection..");
	  Serial.print("**free MEMEORY :");
	  Serial.println(freeMemory(),DEC);
	  
	  if(ether.startup(2))		//startup with timeout // set startup settings and connecgt
	  {
		  Serial.print("**free MEMEORY :");
		  Serial.println(freeMemory(),DEC);
		  Serial.println("connected>>>");
		  lcd.home();lcd.print("Connected   ");
		 
		//  serverFailed=false;
	  }
	  else 
	  {
		  Serial.print("**free MEMEORY :");
		  Serial.println(freeMemory(),DEC);
		  Serial.println("Error Connecting");
		  Serial.println("Exiting...");
		  lcd.home(); lcd.print("Error Connecting");
		//  serverFailed=true;
		  //use default mode for checking
		  dev.setDeviceMethod("CHECK");
	  }
	  
	  
	//  Serial.println("free Ram :"+freeMemory());
	  
	  
	  Serial.print("free MEMEORY :");
	  Serial.println(freeMemory(),DEC);
	//  timeServerCheck=millis();
	  
}


void loop()
{
		
		
		
		Serial.print("**free MEMORY :");
		Serial.print(freeMemory(),DEC);
		Serial.print(" TIME : ");
		Serial.println(millis());			
		//above for debugging purposes
		SDrelease();
		gps.getLatLon(location);	//get lattitude and longitude from gps
		userid.isValid=false;
		userID.getID(userid);	//instead a function to get any ID and type
	
		//following if user is not enrolled in fingerprint itself
		//there is two stage enrollment
		//-> one is on the fingerprint module itself
		//-> other is on the server with the id provided/ assigned for a finger
		if(userid.id==F("NULL")&&userid.type==F("FINGERPRINT"))		//specifically for biometric
		{
				lcd.print("Not Registered :(");
				led.notRegistered();
				buzz.notRegistered();
				userid.id="";
		}
		if(userid.isValid==true)	// if a valid id
		{
			buzz.swipe();		//beep buzzer for swipe/thumb successful impression
			
			//following  with ethernet
			//get date time
			String  date,time;
			timeManage.getDateTimeStr(date,time);
			//following function to send data for checking/ receiving and look for its response
			if(ether.checkData(dev.getDeviceMethod(),userid.type,userid.id,dev.getDeviceId(),time,date,location.lat,location.lon)>0)	
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
