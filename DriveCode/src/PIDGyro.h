/*
 * Gyro.h
 *
 *  Created on: May 10, 2017
 *      Author: Admin
 */

#ifndef SRC_PIDGYRO_H_
#define SRC_PIDGYRO_H_

#include "AHRS.h"
#include "Macros.h"
#include "DriveBase.h"

class PIDGyro
{
public:
	PIDGyro(DriveBase* driveBase);
	~PIDGyro();

	float p();
	float i();
	float d();
	bool pid();
	bool setPoint(int angle);
	void reset();

	bool isTurning();

private:

	float calculateError();

	AHRS* nvx;
	DriveBase* driveBase;

	float desired;
	float actual;

	float integratedError;

	float prevError;

	float slope;
};



#endif /* SRC_PIDGYRO_H_ */
