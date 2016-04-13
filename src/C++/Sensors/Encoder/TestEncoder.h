/*
 * Encoder.h
 *
 *  Created on: Mar 28, 2016
 *      Author: Admin
 */

#ifndef SRC_C___SENSORS_ENCODER_TESTENCODER_H_
#define SRC_C___SENSORS_ENCODER_TESTENCODER_H_

class TestEncoder
{
public:
	TestEncoder();
	~TestEncoder();

	int GetEncoderPos();
private:
	CANTalon* Motor;
};



#endif /* SRC_C___SENSORS_ENCODER_TESTENCODER_H_ */
