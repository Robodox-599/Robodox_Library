#include "SwerveDrive.h"


SwerveDrive::SwerveDrive()
{
	frontLeftDrive = new CANTalon(FRONT_LEFT_MOTOR_PORT);
	backLeftDrive = new CANTalon(BACK_LEFT_MOTOR_PORT);
	frontRightDrive = new CANTalon(FRONT_RIGHT_MOTOR_PORT);
	backRightDrive = new CANTalon(BACK_RIGHT_MOTOR_PORT);

	frontLeftSwerve = new CANTalon(FRONT_LEFT_SWERVE_PORT);
	backLeftSwerve = new CANTalon(BACK_LEFT_SWERVE_PORT);
	frontRightSwerve = new CANTalon(FRONT_RIGHT_SWERVE_PORT);
	backRightSwerve = new CANTalon(BACK_RIGHT_SWERVE_PORT);

	navX = new AHRS(SPI::Port::kMXP);

	forwardSpeed = 0;
	turnSpeed = 0;

	driveLeft = 0;
	driveRight = 0;

	navX->ZeroYaw();
	autoTurn = false;

	trigR = 0;
	trigL = 0;
//--------------------------
	error1 = 0;
	error2 = 0;
	alteredValue = 0;
	desiredValue = 0;

	swerveAngle = 0;
}

SwerveDrive::~SwerveDrive()
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
void SwerveDrive::updateLeftMotors(float speed)
{
	frontLeftDrive->Set(-speed);
	backLeftDrive->Set(-speed);
}

/**
 * updateRightMotors: set right motors to desired speed; reverses right motors
 * @param speed is the desired speed input
 */
void SwerveDrive::updateRightMotors(float speed)
{
	frontRightDrive->Set(speed);
	backRightDrive->Set(speed);
}

void SwerveDrive::setTriggerSpeed(float triggerR, float triggerL)
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
void SwerveDrive::setForwardSpeed(float forward)
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
 * setTurnSpeed: update turn speed with joystick input and does PID (straight SwerveDrive)
 * @param turn is the joystick x-axis
 */
void SwerveDrive::setTurnSpeed(float turn)
{
	if(turn >= DEADZONE || turn <= -DEADZONE)
	{
		turnSpeed = turn;

		autoTurn = false;

		desiredValue = 0;
		navX->ZeroYaw();
	}
	else
	{
		turnSpeed = PID(desiredValue, navX->GetYaw(), 0);

		autoTurn = true;

		if(turnSpeed == 0)
		{
			autoTurn = false;
			desiredValue = 0;
			alteredValue = 0;
			navX->ZeroYaw();
		}
	}
}

/**
 * SwerveDrive: get desired speed values and assign them to motors
 * @param turn is the turn speed
 * @param fwd is the fwd/backward speed
 *
 */
void SwerveDrive::drive(float xAxisR, float yAxisR, float yaxisL, int POV)//make sure POV is on the scale from -180 to 180
{
	desiredValue = setReferenceAngle(POV, navX->GetAngle());

	setForwardSpeed(yAxis);
	setTurnSpeed(xAxis);

	setSwerve(yAxisL);

	updateLeftMotors(forwardSpeed - turnSpeed - trigL);
	updateRightMotors(forwardSpeed + turnSpeed - trigR);
}

float SwerveDrive::setReferenceAngle(int angle, float current)//make sure angle is on the scale from -180 to 360
{
	if(angle == -1)
	{
		return current;
	}
	else if(angle > 180)
	{
		return angle - 360;
		autoTurn = true;
	}
	else if(angle <= 180)
	{
		return angle;
		autoTurn = true;
	}

	return current;
}

void SwerveDrive::edgeCase(int change)
{
	if(alteredValue < 0)
	{
		alteredValue += change;
	}
}

float SwerveDrive::shortestPath(float e1, float e2)
{
	if(std::abs(e1) < std::abs(e2))
	{
		return e1;
	}

	return e2;
}

//------------------------------

void SwerveDrive::setSwerve(float Y)
{
	swerveAngle = 360*frontLeftSwerve->GetEncPosition()/1023;		//converting encoder input to degrees using proportions
	desiredValue = 360*asin(Y)/(2*acos(-1));						//calculating angle in terms of left y axis input using arc sine, then converting angle to degrees
	frontLeftSwerve->Set(PID(desiredValue, swerveAngle, 1));

	swerveAngle = 360*frontRightSwerve->GetEncPosition()/1023;
	desiredValue = (360*asin(Y)/(2*acos(-1)));
	frontRightSwerve->Set(PID(desiredValue, swerveAngle, 1));

	swerveAngle = 360*backLeftSwerve->GetEncPosition()/1023;
	desiredValue = (360*asin(Y)/(2*acos(-1)));
	backLeftSwerve->Set(PID(desiredValue, swerveAngle, 1));

	swerveAngle = 360*backRightSwerve->GetEncPosition()/1023;
	desiredValue = (360*asin(Y)/(2*acos(-1)));
	backRightSwerve->Set(PID(desiredValue, swerveAngle, 1));
}

float SwerveDrive::PID(float desired, float current, float kp)
{
	alteredValue = current;

	if(kp == 1)
	{
		edgeCase(180);//change
	}
	else if(kp == 0)
	{
		edgeCase(360);//change
	}

	error1 = desired - current;
	error2 = desired - alteredValue;

	if((error1 <= -.5 || error1 >= .5) && (error2 <= -.5 || error2 >= .5))
	{
		return kp * shortestPath(error1, error2);
	}
	return 0;
}
