/*
 * DriveController.cpp
 *
 *  Created on: May 18, 2017
 *      Author: tons-of-carls
 */

#include "DriveController.h"

DriveController::DriveController()
{
	xbox = new XboxController(XBOX_PORT);

	driveBase = new DriveBase();
	joystickDrive = new JoystickDrive(driveBase, xbox);

	straightDrive = new PIDGyro(driveBase);
}

DriveController::~DriveController()
{
	driveBase = nullptr;
	delete driveBase;

	joystickDrive = nullptr;
	delete joystickDrive;
}

void DriveController::teleopDrive()
{
	Wait(PID_TIME_CONSTANT);

	driveBase->resetSpeeds();

	joystickDrive->drive();

	if(!joystickDrive->isTurning() && !straightDrive->isTurning())
	{
		straightDrive->pid();
	}
	else
	{
		straightDrive->reset();
	}

	driveBase->updateAllMotors();
}
