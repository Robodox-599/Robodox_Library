/*
 * PIDEncoder.cpp
 *
 *  Created on: May 10, 2017
 *      Author: Admin
 */
#include <PIDEncoder.h>

PIDEncoder::PIDEncoder(DriveBase* driveBase)
{
	this->driveBase = driveBase;

	actual = 0;
	desired = 0;

	integratedError = 0;

	prevError = 0;

	slope = 0;

}

PIDEncoder::~PIDEncoder()
{
	driveBase = nullptr;
	delete driveBase;
}

float PIDEncoder::calculateError()
{
	actual = driveBase->getAverageEncPos();
	return desired - actual;
}

float PIDEncoder::p()
{
	return calculateError() * ENCODER_KP;
}

float PIDEncoder::i()
{
	if(calculateError() != 0)
	{
		integratedError += calculateError() * PID_TIME_CONSTANT;
	}
	else
	{
		integratedError = 0;
	}
	return integratedError * ENCODER_KI;
}

float PIDEncoder::d()
{
	slope = (calculateError() - prevError) / PID_TIME_CONSTANT;
	prevError = calculateError();
	return slope * ENCODER_KD;
}

bool PIDEncoder::pid()
{
	if(calculateError() == 0)
	{
		reset();
		return true;
	}
	else
	{
		driveBase->addTurnSpeed(p() + i() + d());
		return false;
	}
}

bool PIDEncoder::setPoint(int inches)
{
	desired = inches * conversionFactor();
	return pid();
}

void PIDEncoder::reset()
{
	driveBase->zeroEncoders();

	actual = 0;
	desired = 0;

	integratedError = 0;

	prevError = 0;

	slope = 0;
}

float PIDEncoder::conversionFactor()
{
	return TICKS_PER_ROTATION / (DRIVE_WHEEL_DIAMETER * PI);
}
