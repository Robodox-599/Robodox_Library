#include "Drive.h"

Drive::Drive()
{
	frontLeftDrive = new CANTalon(FRONT_LEFT_MOTOR_PORT);
	backLeftDrive = new CANTalon(BACK_LEFT_MOTOR_PORT);
	frontRightDrive = new CANTalon(FRONT_RIGHT_MOTOR_PORT);
	backRightDrive = new CANTalon(BACK_RIGHT_MOTOR_PORT);

	navX = new AHRS(SPI::Port::kMXP);

	forwardSpeed = 0;//
	turnSpeed = 0;//

	driveLeft = 0;
	driveRight = 0;

	error360 = 0;//
	error180 = 0;//

	navX->ZeroYaw();//
	autoTurn = false;//
	gyroValue = navX->GetYaw();//
	referenceAngle = navX->GetYaw();//

	trigR = 0;
	trigL = 0;
}

Drive::~Drive()
{
	delete frontLeftDrive;
	delete backLeftDrive;
	delete frontRightDrive;
	delete backRightDrive;
	delete navX;

	frontLeftDrive = nullptr;
	backLeftDrive = nullptr;
	frontRightDrive = nullptr;
	backRightDrive = nullptr;
	navX = nullptr;
}

/**
 * updateLeftMotors: set left motors to desired speed
 * @param speed is the desired speed input
 */
void Drive::updateLeftMotors(float speed)
{
	frontLeftDrive->Set(-speed);
	backLeftDrive->Set(-speed);
}

/**
 * updateRightMotors: set right motors to desired speed; reverses right motors
 * @param speed is the desired speed input
 */
void Drive::updateRightMotors(float speed)
{
	frontRightDrive->Set(speed);
	backRightDrive->Set(speed);
}

void Drive::setTriggerSpeed(float triggerR, float triggerL)
{
	if(triggerR > DEADZONE)
	{
		trigR = triggerR;
	}
	else
	{
		trigR = 0;
	}

	if(triggerL > DEADZONE)
	{
		trigL = triggerL;
	}
	else
	{
		trigL = 0;
	}
}

/**
 * setForwardSpeed: update forward speed with joystick input
 * @param speed is the joystick y-axis
 */
void Drive::setForwardSpeed(float forward)
{
	if(forward >= DEADZONE || forward <= -DEADZONE)
	{
		forwardSpeed = forward;
	}
	else
	{
		forwardSpeed = 0;
	}
}

/**
 * setTurnSpeed: update turn speed with joystick input and does PID (straight drive)
 * @param turn is the joystick x-axis
 */
void Drive::setTurnSpeed(float turn)
{
	if(turn >= DEADZONE || turn <= -DEADZONE)
	{
		turnSpeed = turn;

		autoTurn = false;

		referenceAngle = 0;
		navX->ZeroYaw();
	}
	else if((error360 <= -.5 || error360 >= .5) && (error180 <= -.5 || error180 >= .5))
	{
		turnSpeed = KP * shortestPath();
	}
	else
	{
		turnSpeed = 0;
		autoTurn = false;
		navX->ZeroYaw();
		gyroValue = 0;
		referenceAngle = 0;
	}
}

/**
 * drive: get desired speed values and assign them to motors
 * @param turn is the turn speed
 * @param fwd is the fwd/backward speed
 *
 */
void Drive::drive(float xAxis, float yAxis, int POV)//make sure POV is on the scale from -180 to 180
{
	gyroValue = navX->GetYaw();

	edgeCase();
	setReferenceAngle(POV);

	error360 = referenceAngle - gyroValue;
	error180 = referenceAngle - navX->GetYaw();

	shortestPath();

	setForwardSpeed(yAxis);
	setTurnSpeed(xAxis);

	updateLeftMotors(forwardSpeed - turnSpeed - trigL);
	updateRightMotors(forwardSpeed + turnSpeed - trigR);
}

void Drive::setReferenceAngle(int angle)//make sure angle is on the scale from -180 to 180
{
	if(angle == -1)
	{

	}
	else if(angle > 180)
	{
		referenceAngle = angle - 360;
		autoTurn = true;
	}
	else if(angle <= 180)
	{
		referenceAngle = angle;
		autoTurn = true;
	}
}

void Drive::edgeCase()
{
	if(gyroValue < 0)
	{
		gyroValue += 360;
	}
}

float Drive::shortestPath()
{
	if(std::abs(error180) < std::abs(error360))
	{
		return error180;
	}

	return error360;
}
