/*
 * Drive.cpp
 *
 *  Created on: Mar 27, 2016
 *      Author: Robodox 599
 */
//Gyro and
#include "Drive.h"

Drive::Drive()
{

	navX = new AHRS(SPI::Port::kMXP);

	//left drive
	frontLeftDrive = new Talon(0);	//port 13
	backLeftDrive = new Talon(1);	//port 15
	frontRightDrive = new Talon(3);	//port 0
	backRightDrive = new Talon(2);	//port 2

	forwardSpeed = 0;
	turnSpeed = 0;

	navX->ZeroYaw();

	gyroValue = navX->GetYaw();
	refAngle = gyroValue;
	gyroDeriv = 0;
	error = 0;
}


Drive::~Drive()
{
	//left drive
	delete frontLeftDrive;
	delete backLeftDrive;

	//right drive
	delete frontRightDrive;
	delete backRightDrive;

	//left drive
	frontLeftDrive = nullptr;
	backLeftDrive = nullptr;

	//right drive
	frontRightDrive = nullptr;
	backRightDrive = nullptr;
}


/*************************************************/

/**
 * drive: get desired speed values and assign them to motors
 * @param xAxis is the joystick x-axis
 * @param yAxis is the joystick y-axis
 *
 */
void Drive::drive(float xAxis, float yAxis)
{
	gyroValue = navX->GetYaw();

	error = refAngle - gyroValue;

	setForwardSpeed(yAxis);
	setTurnSpeed(xAxis);

	updateLeftMotors(forwardSpeed - turnSpeed);
	updateRightMotors(forwardSpeed + turnSpeed);
}

/**
 * setForwardSpeed: update forward speed with input
 * @param forward is the forward/backward speed
 */
void Drive::setForwardSpeed(float forward)
{
	if(forward >= .3)
	{
		forwardSpeed = forward*forward;
	}
	else if(forward <= -.3)
	{
		forwardSpeed = -forward*forward;
	}
	else
	{
		forwardSpeed = 0;
	}
}

/**
 * setTurnSpeed: update turn speed with input
 * @param turn is the turn speed
 */
void Drive::setTurnSpeed(float turn)//continuous turning problem
{
	if(turn >= .3)
	{
		navX->ZeroYaw();
		gyroValue = navX->GetYaw();
		refAngle = gyroValue;

		turnSpeed = turn*turn;
	}
	else if(turn <= -.3)
	{
		navX->ZeroYaw();
		gyroValue = navX->GetYaw();
		refAngle = gyroValue;

		turnSpeed = -turn*turn;
	}
	else if(error >= .5 || error <= -.5)
	{
		turnSpeed = kp * error;
	}
	else
	{
		turnSpeed = 0;
	}
}

/**
 * updateLeftMotors: set left motors to desired speed
 * @param speed is the desired speed input
 */
void Drive::updateLeftMotors(float speed)//put on an x^2 curve
{
	frontLeftDrive->Set(-speed);//2x speed note
	backLeftDrive->Set(-speed);
}

/**
 * updateRightMotors: set right motors to desired speed; reverses right motors
 * @param speed is the desired speed input
 */
void Drive::updateRightMotors(float speed)
{
	frontRightDrive->Set(speed);
	backRightDrive->Set(speed);
}
