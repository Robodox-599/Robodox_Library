/*
 * PIDGyro.cpp
 *
 *  Created on: May 10, 2017
 *      Author: Admin
 */
#include <PIDGyro.h>

PIDGyro::PIDGyro(DriveBase* driveBase)
{
	nvx = new AHRS(SPI::Port::kMXP);
	this->driveBase = driveBase;

	actual = 0;
	desired = 0;

	integratedError = 0;

	prevError = 0;

	slope = 0;

}

PIDGyro::~PIDGyro()
{
	nvx = nullptr;
	delete nvx;

	driveBase = nullptr;
	delete driveBase;
}

float PIDGyro::calculateError()
{
	actual = nvx->GetAngle();
	return desired - actual;
}

float PIDGyro::p()
{
	return calculateError()* STRAIGHT_DRIVE_KP;
}

float PIDGyro::i()
{
	if(calculateError() != 0)
	{
		integratedError += calculateError() * PID_TIME_CONSTANT;
	}
	else
	{
		integratedError = 0;
	}
	return integratedError * STRAIGHT_DRIVE_KI;
}

float PIDGyro::d()
{
	slope = (calculateError() - prevError) / PID_TIME_CONSTANT;
	prevError = calculateError();
	return slope * STRAIGHT_DRIVE_KD;
}

bool PIDGyro::pid()
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

bool PIDGyro::setPoint(int angle)
{
	desired = angle;
	return pid();
}

void PIDGyro::reset()
{
	nvx->ZeroYaw();

	actual = 0;
	desired = 0;

	integratedError = 0;

	prevError = 0;

	slope = 0;
}


bool PIDGyro::isTurning()
{
	return nvx->GetRate() > TURNING_THREASHOLD && nvx->GetRate() < -TURNING_THREASHOLD;
}
