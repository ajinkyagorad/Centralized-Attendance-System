#include <Wire.h>
#include <Fingerprint.h>
#include <SD.h>
#include <GSM.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <DS1307.h>
/*
 * accessControl_AR.ino
 *
 * Created: 5/8/2015 5:20:20 AM
 * Author: Ajinkya
 *NOTE:
	while using SD card:
		deselectEthernet ie make CS pin of EThernet high
	and while using ethernet 
		deselect SD card ie make CS pin of SD high
	MACROS:
		SDrelease() releases SD bus;
		ETrelease() releases ETh bus
 */ 
#include "RFID.h"
#include "wiznet.h"
#include "time.h"
#include "lcd.h"
#include "RGBled.h"
#include "buzzer.h"
#include "memory.h"
/***********************/
LCD lcd(22,23,24,25,26,27,28);
wiznet ether;
EthernetClient client;
DS1307 clock;
RGBLED led(5,6,7);
buzzer buzz(8);
memory disk(4);		//chip select  for sd card
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
bool transmittedFiles;
void setup()
{

	  /* add setup code here, setup code runs once when the processor starts */
	  pinMode(10,OUTPUT);	//for ethernet
	  pinMode(4,OUTPUT);	//for SD 
	  Serial.begin(9600);
	  SDrelease();
	  RFID::init();
	  ether.init();
	  clock.begin();
	  lcd.begin(16,2);
	  if(!disk.init())
	  {
		  Serial.println("unable to initialise SD card");
	  }
	  lcd.print("initialised");
	  Serial.println("Initialised");
	  lcd.home();lcd.print("connecting...");
	  Serial.println("Waiting for connection..");
	  if(ether.startup(60))
	  {
		  Serial.println("connected>>>");
		  lcd.home();lcd.print("Connected   ");
		  //after CONNECTING DO DEVICE ID AND PARSING s
		  //add support for time adjustment
		  serverFailed=false;
	  }
	  else 
	  {
		  Serial.println("Error Connecting");
		  Serial.println("Exiting...");
		  lcd.home(); lcd.print("Error Connecting");
		  serverFailed=true;
	  }
	  timeServerCheck=millis();
}
RFID::id rfid;

void loop()
{
		//wait for first connection  is made :>
		//loop {	
		//if rfid is read , transmit a request;
		//		if connection  problem print :connection problem
		//look for response while client is connected.
		//print response	}
		
		
		SDrelease();
		RFID::getID(rfid);		//instead a function to get any ID and type
		
		if(rfid.isValid==true)	// if a valid id
		{
			buzz.swipe();		//beep buzzer for swipe/thumb successful impression
			
			//following  with ethernet
			if(ether.checkData("CHECK","RFID",rfid.buf,"1","NULL","NULL","NULL","NULL")>0)	//function to send data for checking/ receiving and look for its response
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
				disk.saveData(ether.getDataNotSent());	//save data on sd card
			}
			delay(1000);	// for beep and lcd persistence of message
		}
		else
		{
			lcd.clear();
			led.clear();
			
			lcd.displayDateTime();
		}
		
		//try after every 60 seconds if the server is available and send data if 
		if(millis()-timeServerCheck>60000 && serverFailed)// if time from last was greater than 60sec and serverFailed to connect
		{
			timeServerCheck=millis();// save current time for next check
			/*** CHECK  connection status
				 //if able to connect  
					// check and transmit any pending files
						//if all files transmitted
				// if not connect set serverFailed
				*/
		}
}
