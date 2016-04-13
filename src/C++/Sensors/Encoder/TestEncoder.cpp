/*
 * Encoder.cpp
 *
 *  Created on: Mar 30, 2016
 *      Author: Admin
 */
#include <C++/Sensors/Encoder/TestEncoder.h>

TestEncoder::TestEncoder()
{
	Motor = new CANTalon(1);
}

TestEncoder::~TestEncoder()
{
	Motor = nullptr;

	delete Motor;
}

int TestEncoder::GetEncoderPos()
{
	return Motor->GetEncPosition();
}



