/*
 * FSR.cpp
 *
 *  Created on: Feb 8, 2017
 *      Author: Admin
 */
#include "FSR.h"

FSR::FSR()
{
	fsrReading = 0;
	fsrVoltage = 0;
	fsrResistance = 0;
	fsrConductance = 0;
	fsrForce = 0;

	fsr = new FSR();
}


FSR::~FSR()
{
	fsr = nullptr;

	delete fsr;
}

long FSR::map(int value, int fromLow, int fromHigh, int toLow, int toHigh) //analog voltage reading ranges from 0 to 1023, which maps to 0V to 5V
{
	return ((value - fromLow)*(toHigh - toLow)/(fromHigh - fromLow + toLow));
}

int FSR::returnRawReading()
{
	fsrReading = fsr->GetValue();

	return fsrReading;
}

float FSR::returnVoltage()
{
	returnRawReading();
	fsrVoltage = map(fsrReading, 0, 1023, 0, 5000);

	return fsrVoltage;
}

float FSR::returnResistance()
{
	returnVoltage();

	if(fsrVoltage == 0)	//delete this is not needed
		printf("No Pressure");

	else	//The coltage = Vcc * R / (R+ FSR) wehre R = 10kohm and Vcc = 5V
		fsrResistance = 5000 - fsrVoltage;	// fsrVoltage is in millivolts so 5V = 5000mV -- the map function rounds up the voltage, so to get better accuracy convert it to mV
		fsrResistance*= 10000;	// 10kohm resistor
		fsrResistance/= fsrVoltage;

	return fsrResistance;
}

float FSR::returnConductance()
{
	returnResistance();
	fsrConductance = 1000000; //measured in microohms
	fsrConductance /= fsrResistance;

	return fsrConductance;
}

float FSR::returnForce() //using the two FSR guide graphs to approcimate the force
{
	returnConductance();

	if(fsrConductance <= 1000)
		fsrForce = fsrConductance/80;
	else
		fsrForce = fsrConductance - 1000;
		fsrForce/= 30;

	return fsrForce;
}
