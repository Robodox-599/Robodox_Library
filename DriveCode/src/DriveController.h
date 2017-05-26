/*
 * DriveController.h
 *
 *  Created on: May 18, 2017
 *      Author: tons-of-carls
 */

#ifndef SRC_DRIVECONTROLLER_H_
#define SRC_DRIVECONTROLLER_H_

#include "DriveBase.h"
#include "JoystickDrive.h"
#include "PIDGyro.h"

class DriveController
{
public:
	DriveController();
	~DriveController();

	void teleopDrive();
private:

	DriveBase* driveBase;
	JoystickDrive* joystickDrive;
	PIDGyro* straightDrive;

	XboxController* xbox;


};


#endif /* SRC_DRIVECONTROLLER_H_ */
