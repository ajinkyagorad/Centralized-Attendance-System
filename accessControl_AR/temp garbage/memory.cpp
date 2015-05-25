/*
 * memory.cpp
 *
 * Created: 11-05-2015 10:44:22 PM
 *  Author: Ajinkya
 */ 
#ifndef MEMORY_CPP
#define MEMORY_CPP
#include "memory.h"

memory::memory()
{
	chipSelectPin=4;
}

memory::memory(int csPin)
{
	chipSelectPin=csPin;
}

bool memory::init()
{
	ETrelease();	//make  chipselect of ethernet high 
	bool isDone=SD.begin(chipSelectPin);
	SDrelease();
	return isDone;
	
}

void memory::saveData(String data)
{
	ETrelease();
	char lastIndexFilename[20]="lastIndex.txt";
	int index=0;
	if(SD.exists(lastIndexFilename))
	{
		//open file if exist and get index to last  file 
		File lastIndex=SD.open(lastIndexFilename,FILE_READ);
		 index=String(lastIndex.readString()).toInt();
		 lastIndex.close();
	}
	else
	{
		//file does not exists and need to be created
	}
	{
		//create file
		File lastIndex=SD.open(lastIndexFilename,FILE_WRITE);
		lastIndex.print("0");
		lastIndex.close();
	}
	//increment  index
	index++;
	//
	//save  data in file
	//create new file at index
	char id[20];
	itoa(index,id,10);
	File dataFile=SD.open(id,FILE_WRITE);
	dataFile.print(data);
	dataFile.close();
	
	//update  lastIndex
	SD.remove(lastIndexFilename);
	File lastIndex=SD.open(lastIndexFilename,FILE_WRITE);
	lastIndex.print(index);
	lastIndex.close();
	
	
	/*release  SD chip select*/
	SDrelease();
	
	
	
}

#endif