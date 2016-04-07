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

class SwerveDrive
{
public:
	SwerveDrive();
	~SwerveDrive();

	void updateLeftMotors(float speed);
	void updateRightMotors(float speed);

	void setForwardSpeed(float rawY);
	void setTurnSpeed(float rawX, int pov);
	void setTriggerSpeed(float triggerR, float triggerL);

	void drive(float xAxis, float yAxis, int POV);

	float setReferenceAngle(int angle, float current);
	void edgeCase(int change);
	float shortestPath(float e1, float e2);
	float linearizeDrive(float driveInput);

	void driveMotors(float turn, float fwd);
//--------------------------------------------------
	float PID(float desired, float current, float kp);
	float shortest(float e1, float e2);//shortest path function

	AHRS* navX;

	float forwardSpeed;
	float turnSpeed;

	float driveLeft;
	float driveRight;

	float trigL;
	float trigR;

	bool autoTurn;
//----------------------------------------
	float error1;
	float error2;
	float alteredValue;//gyrovalue
	float desiredValue;//referenceangle

private:
	CANTalon* frontLeftDrive;
	CANTalon* backLeftDrive;
	CANTalon* frontRightDrive;
	CANTalon* backRightDrive;

	CANTalon* frontLeftSwerve;
	CANTalon* backLeftSwerve;
	CANTalon* frontRightSwerve;
	CANTalon* backRightSwerve;


};


#endif /* SRC_GYRODRIVE_GYRODRIVE_H_ */
