/*
 * Drive.h
 *
 *  Created on: Mar 27, 2016
 *      Author: Robodox 599
 */

#ifndef SRC_DRIVE_DRIVE_H_
#define SRC_DRIVE_DRIVE_H_

#include "WPILib.h"
#include "AHRS.h"

class Drive
{
public:
	Drive();
	~Drive();

	void drive(float xAxis, float yAxis);

	void setForwardSpeed(float rawY);
	void setTurnSpeed(float rawX);

	void updateLeftMotors(float speed);
	void updateRightMotors(float speed);

	AHRS* navX;

	Talon* frontLeftDrive;
	Talon* backLeftDrive;
	Talon* frontRightDrive;
	Talon* backRightDrive;

	float error;

private:
	float forwardSpeed;
	float turnSpeed;

	//Straight Drive Variables
	float gyroValue;

	float refAngle;
	float gyroDeriv;

	float const kp = 0.01;

};



#endif /* SRC_DRIVE_DRIVE_H_ */
