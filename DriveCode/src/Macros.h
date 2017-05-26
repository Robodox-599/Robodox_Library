/*
 * Macros.h
 *
 *  Created on: May 11, 2017
 *      Author: tons-of-carls
 */

#ifndef SRC_MACROS_H_
#define SRC_MACROS_H_

//DRIVEBASE
#define FRONT_LEFT_DRIVE_PORT				(7)	//encoder talon
#define BACK_LEFT_DRIVE_PORT				(10)
#define FRONT_RIGHT_DRIVE_PORT				(8)	//encoder talon
#define BACK_RIGHT_DRIVE_PORT				(6)

#define SHIFTER_PORT_A						(0)
#define SHIFTER_PORT_B						(1)

#define FRONT_BACK_SWITCH					(-1)
#define TURN_SWITCH							(-1)

//JOYSTICKDRIVE
#define JOYSTICK_TURN_DEADZONE				(0.17)
#define JOYSTICK_FORWARD_DEADZONE			(0.05)

	//Ay^2 + By + C
	//where y is the y' axis of the joystick
#define FORWARD_EQUATION_A					(1)		//A
#define FORWARD_EQUATION_B					(0.1)	//B
#define FORWARD_EQUATION_C					(0.0025)//C

	//( M ) * ( Ax^2 + Bx + C ) * ( 1 - ( F * y ) )
	//where x is the x' axis of the joystick
	//where y is the forward speed component
#define TURN_EQUATION_A						(1)		//A
#define TURN_EQUATION_B						(0.1)	//B
#define TURN_EQUATION_C						(0.0025)//C
#define TURN_EQUATION_MAIN_ADJUSTMENT		(0.5)	//M, Range:[1,0)
#define TURN_EQUATION_FORWARD_ADJUSTMENT	(0.48)	//F, Range:[1,0]

//DRIVECONTROLLER
#define XBOX_PORT							(0)

//PIDENCODER
#define ENCODER_KP							(.01)
#define ENCODER_KI							(.001)
#define ENCODER_KD							(.001)

#define DRIVE_WHEEL_DIAMETER				(4)
#define PI									(3.1415927)

#define TICKS_PER_ROTATION					(1024)

//PIDGYRO
#define STRAIGHT_DRIVE_KP					(.01)
#define STRAIGHT_DRIVE_KI					(.00001)
#define STRAIGHT_DRIVE_KD					(.00001)

#define TURNING_THREASHOLD					(.5)

//GENERAL
#define PID_TIME_CONSTANT					(.1)

#endif /* SRC_MACROS_H_ */
