/*
 * JoystickDrive.cpp
 *
 *  Created on: May 10, 2017
 *      Author: tons-of-carls
 */

#include "JoystickDrive.h"

JoystickDrive::JoystickDrive(DriveBase* driveBase, XboxController* xbox)
{
	this->xbox = xbox;

	this->driveBase = driveBase;

	joystickForward = 0;
	joystickTurn = 0;

	reverseControls = 1;
}

JoystickDrive::~JoystickDrive()
{
	xbox = nullptr;
	delete xbox;
}

void JoystickDrive::drive()
{
	reverseDrive();
	shiftGear();

	setJoystickForward();
	setJoystickTurn();

	updateForwardSpeed();
	updateTurnSpeed();
}

float JoystickDrive::calcJoystickForward(bool positive)
{
	if(positive)
	{
		return FORWARD_EQUATION_A * pow(getJoystickForward(),2) + FORWARD_EQUATION_B * getJoystickForward() + FORWARD_EQUATION_C;//(getJoystickForward() - .05) * (getJoystickForward() - .05);
	}
	else
	{
		return -FORWARD_EQUATION_A * pow(getJoystickForward(),2) - FORWARD_EQUATION_B * getJoystickForward() - FORWARD_EQUATION_C;//-(-getJoystickForward() - .05) * (-getJoystickForward() - .05);
	}
}


float JoystickDrive::calcJoystickTurn(bool positive)
{
	if(positive)
	{
		return TURN_EQUATION_MAIN_ADJUSTMENT * (TURN_EQUATION_A * pow(getJoystickTurn(),2) + TURN_EQUATION_B * getJoystickTurn() + TURN_EQUATION_C) * (1 - (TURN_EQUATION_FORWARD_ADJUSTMENT * abs(joystickForward)));//.5 * (getJoystickTurn() - .05) * (getJoystickTurn() - .05) * (1 - (.48*abs(joystickForward)));
	}
	else
	{
		return TURN_EQUATION_MAIN_ADJUSTMENT * (-TURN_EQUATION_A * pow(getJoystickTurn(),2) - TURN_EQUATION_B * getJoystickTurn() - TURN_EQUATION_C) * (1 - (TURN_EQUATION_FORWARD_ADJUSTMENT * abs(joystickForward)));//-.5 * (-getJoystickTurn() - .05) * (-getJoystickTurn() - .05) * (1 - (.48*abs(joystickForward)));
	}
}

void JoystickDrive::setJoystickForward()
{
	if(getJoystickForward() >= JOYSTICK_FORWARD_DEADZONE)
	{
		joystickForward = calcJoystickForward(true);
	}
	else if(getJoystickForward() <= -JOYSTICK_FORWARD_DEADZONE)
	{
		joystickForward = calcJoystickForward(false);
	}
	else
	{
		joystickForward = 0;
	}
}

void JoystickDrive::setJoystickTurn()
{
	if(getJoystickTurn() >= JOYSTICK_TURN_DEADZONE)
	{
		joystickTurn = calcJoystickTurn(true);
	}
	else if(getJoystickTurn() <= -JOYSTICK_TURN_DEADZONE)
	{
		joystickTurn = calcJoystickTurn(false);
	}
	else
	{
		joystickTurn = 0;
	}
}

void JoystickDrive::updateForwardSpeed()
{
	driveBase->addTurnSpeed(joystickTurn);
}

/*
 * updateTurnSpeed: gives the
 */
void JoystickDrive::updateTurnSpeed()
{
	driveBase->addForwardSpeed(joystickForward);
}

/*
 * getJoystickTurn: returns the value of the joystick axis responsible for moving forward
 */
float JoystickDrive::getJoystickForward()
{
	return -(reverseControls * xbox->GetY(XboxController::kLeftHand));
}

/*
 * getJoystickTurn: returns the value of the joystick axis responsible for turning
 */
float JoystickDrive::getJoystickTurn()
{
	return xbox->GetX(XboxController::kRightHand);
}

/*
 * reverseDrive: switches the front and back of the robot
 */
void JoystickDrive::reverseDrive()
{
	if(xbox->GetBumper(XboxController::JoystickHand::kLeftHand) ||
		xbox->GetBumper(XboxController::JoystickHand::kRightHand))
	{
		reverseControls = -1;
	}
	else
	{
		reverseControls = 1;
	}
}

/**
 * shiftGear: changes the drive between high gear and low gear
 */
void JoystickDrive::shiftGear()
{
	driveBase->shift(xbox->GetBButton());
}

/*
 * isTurning: return true if the driver is turning the robot
 */
bool JoystickDrive::isTurning()
{
	return joystickTurn != 0;
}

/*
 * isMovingForward: returns true if the driver is driving the robot forward or backwards
 */
bool JoystickDrive::isMovingForward()
{
	return joystickForward != 0;
}














