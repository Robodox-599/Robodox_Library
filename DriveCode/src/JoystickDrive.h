/*
 * JoystickDrive.h
 *
 *  Created on: May 10, 2017
 *      Author: tons-of-carls
 */

#ifndef SRC_JOYSTICKDRIVE_H_
#define SRC_JOYSTICKDRIVE_H_

#include "WPILib.h"
#include "Macros.h"
#include "DriveBase.h"

class JoystickDrive
{
public:
	JoystickDrive(DriveBase* driveBase, XboxController* xbox);
	~JoystickDrive();

	void drive();

	bool isTurning();
	bool isMovingForward();

private:

	float calcJoystickTurn(bool positive);
	float calcJoystickForward(bool positive);

	void setJoystickTurn();
	void setJoystickForward();

	void updateTurnSpeed();
	void updateForwardSpeed();

	float getJoystickForward();
	float getJoystickTurn();

	void reverseDrive();

	void shiftGear();

	XboxController* xbox;
	DriveBase* driveBase;

	float joystickTurn;
	float joystickForward;

	int reverseControls;
};


#endif /* SRC_JOYSTICKDRIVE_H_ */
