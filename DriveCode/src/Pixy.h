/*
 * Pixy.h
 *
 *  Created on: Jan 8, 2017
 *      Author: Admin
 */
#include "WPILib.h"
#ifndef SRC_PIXY_H_
#define SRC_PIXY_H_

class Pixy
{
public:
	Pixy();
	~Pixy();

	I2C* Sensor;

	enum Value
	{
		CHECKSUM,
		SIGNATURE,
		X_CENTER,
		Y_CENTER,
		WIDTH,
		HEIGHT
	};

	bool updateBuffer();
	uint16_t getValue(Value v);
	bool getBlockStatus();

	bool fillBlock(uint16_t block[]);

private:

	void convert(int byteOne, int byteTwo, uint16_t block[]);

	uint8_t sync[2];
	uint8_t buffer[28];

	uint16_t pixyLeftValues[6];
	uint16_t pixyRightValues[6];
	int blockRecieved;

};



#endif /* SRC_PIXY_H_ */
