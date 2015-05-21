/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Mega w/ ATmega2560 (Mega 2560), Platform=avr, Package=arduino
*/

#define __AVR_ATmega2560__
#define ARDUINO 161
#define ARDUINO_MAIN
#define F_CPU 16000000L
#define __AVR__
extern "C" void __cxa_pure_virtual() {;}

//
//

#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\variants\mega\pins_arduino.h" 
#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\arduino.h"
#include <accessControl_AR.ino>
#include <RFID.cpp>
#include <RFID.h>
#include <RGBled.cpp>
#include <RGBled.h>
#include <SIM.cpp>
#include <SIM.h>
#include <buzzer.cpp>
#include <buzzer.h>
#include <devid.cpp>
#include <devid.h>
#include <lcd.cpp>
#include <lcd.h>
#include <memory.cpp>
#include <memory.h>
#include <time.cpp>
#include <time.h>
#include <wiznet.cpp>
#include <wiznet.h>
