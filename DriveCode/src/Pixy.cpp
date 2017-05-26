/*
 * Pixy.cpp
 *
 *  Created on: Jan 8, 2017
 *      Author: Admin
 */
#include "Pixy.h"

Pixy::Pixy()
{
	Sensor = new I2C(I2C::Port::kOnboard, 0x2);
	buffer[28] = {};
	sync[2] = {};
	pixyLeftValues[6] = {};
	pixyRightValues[6] = {};
	blockRecieved = 0;
}

Pixy::~Pixy()
{
	delete Sensor;
	Sensor = nullptr;
}


//Byte one: 0101 0101
//Byte two: 1010 1010

// << : 1010 1010 0000 0000
// | : 1010 1010 0000 0000 + 0101 0101 = 1010 1010 0101 0101
void Pixy::convert(int byteOne, int byteTwo, uint16_t block[])
{
	block[byteOne/2] = buffer[byteOne] | (buffer[byteTwo] << 8);
}

bool Pixy::updateBuffer()
{
	Sensor->Transaction(NULL, 0, sync, 1);
	if(sync[0] == 85)
	{
		Sensor->Transaction(NULL, 0, sync, 1);
		if(sync[0] == 170)
		{
			return fillBlock(pixyLeftValues) && fillBlock(pixyRightValues);
		}
	}
	return false;
}

uint16_t Pixy::getValue(Value v)
{
	return (pixyLeftValues[v] + pixyRightValues[v])/2;
}

bool Pixy::fillBlock(uint16_t block[])
{
	Sensor->Transaction(NULL, 0, sync, 1);
	if(sync[0] == 85)
	{
		Sensor->Transaction(NULL, 0, sync, 1);
		if(sync[0] == 170)
		{
			Sensor->Transaction(NULL, 0, buffer, 12);
			convert(0,1,block);
			convert(2,3,block);
			convert(4,5,block);
			convert(6,7,block);
			convert(8,9,block);
			convert(10,11,block);

			if(block[0] == block[1] + block[2] + block[3] + block[4] + block[5])
			{
				return true;
			}
		}
	}
	return false;
}

bool Pixy::getBlockStatus()
{
	if(pixyLeftValues[X_CENTER] - pixyRightValues[X_CENTER] < 2 ||  pixyRightValues[X_CENTER] - pixyLeftValues[X_CENTER] < 2)
	{
		return false;
	}

	return true;
}
