#include "Shooter.h"

Shooter::Shooter()
{
	shooterMotor = new CANTalon(6);//SHOOTER_MOTOR_CHANNEL);
	gearPiston = new DoubleSolenoid(GEAR_PISTON_CHANNEL_A, GEAR_PISTON_CHANNEL_B);
	limit = new DigitalInput(8);

	shooterMotor->ConfigFwdLimitSwitchNormallyOpen(true);
	safetyPressed = false;

	speed = 0;
}

Shooter::~Shooter()
{
	delete shooterMotor;
	delete gearPiston;
	delete limit;

	shooterMotor = nullptr; 
	gearPiston = nullptr;
	limit = nullptr;
}

bool Shooter::getLimit()
{
	return limit->Get();
}

void Shooter::catapultReset(bool reset)
{
	/*if(shooterMotor->GetEncPosition() > 10)
	{
		shooterMotor->Set(0);
	}*/
	if(reset == true && !getLimit())
	{
		shooterMotor->Set(.1); //WARNING: DO NOT MAKE NEGATIVE (and may need to change value)
	}
	else
	{
		shooterMotor->Set(0);
	}
}

void Shooter::catapultLaunch(bool fwdPiston, bool safety)
{
	if(fwdPiston and safety)
	{
		gearPiston->Set(DoubleSolenoid::Value::kForward);
		Wait(2);
		gearPiston->Set(DoubleSolenoid::Value::kReverse);
	}
	/*else if(revPiston)
	{
		gearPiston->Set(DoubleSolenoid::Value::kReverse);
	}
	else
	{
		gearPiston->Set(DoubleSolenoid::Value::kOff);
	}*/
}

double Shooter::getMotorSpeed()
{
	return shooterMotor->GetSpeed();
}

int Shooter::getEncPos()
{
	return shooterMotor->GetEncPosition();
}
