/*
 * Gyro.h
 *
 *  Created on: May 10, 2017
 *      Author: Admin
 */

#ifndef SRC_PIDEncoder_H_
#define SRC_PIDEncoder_H_

#include "AHRS.h"
#include "Macros.h"
#include "DriveBase.h"

class PIDEncoder
{
public:
	PIDEncoder(DriveBase* driveBase);
	~PIDEncoder();

	float p();
	float i();
	float d();
	bool pid();
	bool setPoint(int inches);
	void reset();

private:

	float calculateError();
	float conversionFactor();

	DriveBase* driveBase;

	float desired;
	float actual;

	float integratedError;

	float prevError;

	float slope;
};



#endif /* SRC_PIDGYRO_H_ */
