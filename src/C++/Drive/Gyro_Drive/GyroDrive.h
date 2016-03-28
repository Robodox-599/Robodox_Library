/*
 * GyroDrive.h
 *
 *  Created on: Mar 27, 2016
 *      Author: Robodox 599
 */

#ifndef SRC_GYRODRIVE_GYRODRIVE_H_
#define SRC_GYRODRIVE_GYRODRIVE_H_

#include "wpilib.h"

#include "../Macros.h"
#include "AHRS.h"

class Drive
{
public:
	Drive();
	~Drive();

	void updateLeftMotors(float speed);
	void updateRightMotors(float speed);

	void setForwardSpeed(float rawY);
	void setTurnSpeed(float rawX);
	void setTriggerSpeed(float triggerR, float triggerL);

	void drive(float xAxis, float yAxis, int POV);

	void setReferenceAngle(int angle);
	void edgeCase();
	float shortestPath();
	float linearizeDrive(float driveInput);

	void driveMotors(float turn, float fwd);

	AHRS* navX;

	float referenceAngle;

	float forwardSpeed;
	float turnSpeed;

	float driveLeft;
	float driveRight;

	float trigL;
	float trigR;

	float error360;
	float error180;
	float gyroValue;

	bool autoTurn;

private:
	CANTalon* frontLeftDrive;
	CANTalon* backLeftDrive;
	CANTalon* frontRightDrive;
	CANTalon* backRightDrive;

};


#endif /* SRC_GYRODRIVE_GYRODRIVE_H_ */
