/*
 * Drive.h
 *
 *  Created on: Jan 30, 2017
 *      Author: tons-of-carls
 */

#ifndef SRC_DRIVEBASE_H_
#define SRC_DRIVEBASE_H_

#include "WPILib.h"
#include "CANTalon.h"
#include "Macros.h"
#include <cmath>

using namespace std;

class DriveBase
{
public:
	DriveBase();
	~DriveBase();

	void resetSpeeds();

	void addForwardSpeed(float increment);
	void addTurnSpeed(float increment);

	void addRightSpeed(float increment);
	void addLeftSpeed(float increment);

	void updateAllMotors();

	void setLowGear();
	void setHighGear();

	int getLeftEncoderPos();
	int getRightEncoderPos();
	int getAverageEncPos();
	void zeroEncoders();

	void shift(bool toggleShift);
	void setRampRates(int voltage);

	string getShiftState();



private:

	void updateLeftMotors();
	void updateRightMotors();

	void setRightSpeed();
	void setLeftSpeed();

	CANTalon* frontLeftDrive;
	CANTalon* backLeftDrive;
	CANTalon* frontRightDrive;
	CANTalon* backRightDrive;

	DoubleSolenoid* shifter;

	bool shifterButtonPress;

	float forwardSpeed;
	float turnSpeed;

	float rightSpeed;
	float leftSpeed;

};


#endif /* SRC_DRIVEBASE_H_ */
