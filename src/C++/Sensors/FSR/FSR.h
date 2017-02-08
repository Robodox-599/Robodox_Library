/*
 * FSR.h
 *
 *  Created on: Feb 8, 2017
 *      Author: Admin
 */

#ifndef SRC_C___SENSORS_FSR_FSR_H_
#define SRC_C___SENSORS_FSR_FSR_H_

#include "WPILib.h"

class FSR
{

public:
	FSR();
	~FSR();

	long map(int value, int fromLow, int fromHigh, int toLow, int toHigh);
	int returnRawReading();
	float returnVoltage();
	float returnResistance();
	float returnConductance();
	float returnForce();

private:
	int fsrReading;
	float fsrVoltage;
	float fsrResistance;
	float fsrConductance;
	float fsrForce;

	AnalogInput* fsr;
};



#endif /* SRC_C___SENSORS_FSR_FSR_H_ */
