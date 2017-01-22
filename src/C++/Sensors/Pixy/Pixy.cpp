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
	buffer[12] = {};
	sync[2] = {};
	pixyValues[6] = {};
}

Pixy::~Pixy()
{
	delete Sensor;
	Sensor = nullptr;
}

void Pixy::convert(int byteOne, int byteTwo)
{
	pixyValues[byteOne/2] = buffer[byteOne] | (buffer[byteTwo] << 8);
}

bool Pixy::updateBuffer()
{
	Sensor->Transaction(NULL, 0, sync, 1);
	if(sync[0] == 85)
	{
		Sensor->Transaction(NULL, 0, sync, 1);
		if(sync[0] == 170)
		{
			Sensor->Transaction(NULL, 0, sync, 1);
			if(sync[0] == 85)
			{
				Sensor->Transaction(NULL, 0, sync, 1);
				if(sync[0] == 170)
				{
					Sensor->Transaction(NULL, 0, buffer, 12);
					convert(0,1);
					convert(2,3);
					convert(4,5);
					convert(6,7);
					convert(8,9);
					convert(10,11);
					return true;
				}
			}
		}
	}
	else if(sync[0] == 0)
	{
		//no object detected
		//place appropriate code
	}
	return false;
}

uint16_t Pixy::getValue(Value v)
{
	return pixyValues[v];
}
