/*
 * DriveBase.cpp
 *
 *  Created on: Jan 30, 2017
 *      Author: tons-of-carls
 */

#include "DriveBase.h"

DriveBase::DriveBase()
{
	//Left DriveBase
	frontLeftDrive = new CANTalon(FRONT_LEFT_DRIVE_PORT);
	backLeftDrive = new CANTalon(BACK_LEFT_DRIVE_PORT);

	//Right DriveBase
	frontRightDrive = new CANTalon(FRONT_RIGHT_DRIVE_PORT);
	backRightDrive = new CANTalon(BACK_RIGHT_DRIVE_PORT);

	//Shifter
	shifter = new DoubleSolenoid(SHIFTER_PORT_A,SHIFTER_PORT_B);
	shifterButtonPress = true;

	//general Variables
	forwardSpeed = 0;
	turnSpeed = 0;

	rightSpeed = 0;
	leftSpeed = 0;
}


DriveBase::~DriveBase()
{
	//left DriveBase
	delete frontLeftDrive;
	delete backLeftDrive;

	//right DriveBase
	delete frontRightDrive;
	delete backRightDrive;

	//left DriveBase
	frontLeftDrive = nullptr;
	backLeftDrive = nullptr;

	//right DriveBase
	frontRightDrive = nullptr;
	backRightDrive = nullptr;
}


/*************************************************/


/**
 * updateAllMotors: updates all motors using the updateLeftMotors and updateRightMotors function
 */
void DriveBase::updateAllMotors()
{
	setRightSpeed();
	setLeftSpeed();

	updateLeftMotors();
	updateRightMotors();
}


/**
 * updateLeftMotors: set left motors to desired speed
 * @param speed is the desired speed input
 */
void DriveBase::updateLeftMotors()
{
	frontLeftDrive->Set(-1 * FRONT_BACK_SWITCH * leftSpeed);
	backLeftDrive->Set(-1 * FRONT_BACK_SWITCH * leftSpeed);
}


/**
 * updateRightMotors: set right motors to desired speed; reverses right motors
 * @param speed is the desired speed input
 */
void DriveBase::updateRightMotors()
{
	frontRightDrive->Set(FRONT_BACK_SWITCH * rightSpeed);//positive input motor runs counter clockwise on mod chassis may be because of gear box but check this for every robot
	backRightDrive->Set(FRONT_BACK_SWITCH * rightSpeed);
}


/**
 * addForwardSpeed: increases the forward speed by increment
 * @param increment is the amount to increase the forward speed by
 */
void DriveBase::addForwardSpeed(float increment)
{
	forwardSpeed += increment;
}


/**
 * addTurnSpeed: increases the turn speed by increment
 * @param increment is the amount to increase the turn speed by
 */
void DriveBase::addTurnSpeed(float increment)
{
	turnSpeed += increment;
}


void DriveBase::addRightSpeed(float increment)
{
	rightSpeed += increment;
}


void DriveBase::addLeftSpeed(float increment)
{
	leftSpeed += increment;
}


void DriveBase::setRightSpeed()
{
	rightSpeed += forwardSpeed - TURN_SWITCH * FRONT_BACK_SWITCH * turnSpeed;
}


void DriveBase::setLeftSpeed()
{
	leftSpeed += forwardSpeed + TURN_SWITCH * FRONT_BACK_SWITCH * turnSpeed;
}

void DriveBase::resetSpeeds()
{
	forwardSpeed = 0;
	turnSpeed = 0;

	rightSpeed = 0;
	leftSpeed = 0;
}


int DriveBase::getLeftEncoderPos()
{
	return frontLeftDrive->GetEncPosition();
}


int DriveBase::getRightEncoderPos()
{
	return frontRightDrive->GetEncPosition();
}


int DriveBase::getAverageEncPos()
{
	return (getLeftEncoderPos() + getRightEncoderPos()) / 2;
}

void DriveBase::zeroEncoders()
{
	frontLeftDrive->SetEncPosition(0);
	frontRightDrive->SetEncPosition(0);
}

void DriveBase::shift(bool toggleShift)
{
	if(toggleShift && shifterButtonPress)
	{
		if(shifter->Get() == DoubleSolenoid::Value::kForward)
		{
			shifter->Set(DoubleSolenoid::Value::kReverse);
		}
		else
		{
			shifter->Set(DoubleSolenoid::Value::kForward);
		}
		shifterButtonPress = false;
	}

	if(!toggleShift && !shifterButtonPress)
	{
		shifterButtonPress = true;
	}
}


void DriveBase::setLowGear()
{
	shifter->Set(DoubleSolenoid::Value::kReverse);
}


void DriveBase::setHighGear()
{
	shifter->Set(DoubleSolenoid::Value::kForward);
}


string DriveBase::getShiftState()
{
	if(shifter->Get() == DoubleSolenoid::Value::kForward)
	{
		return "Low Gear";
	}

	return "High Gear";
}


void DriveBase::setRampRates(int voltage)
{
	frontLeftDrive->SetVoltageRampRate(voltage);
	backLeftDrive->SetVoltageRampRate(voltage);

	frontRightDrive->SetVoltageRampRate(voltage);
	backRightDrive->SetVoltageRampRate(voltage);
}



