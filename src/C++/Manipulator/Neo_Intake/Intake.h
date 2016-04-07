#ifndef INTAKE_H_
#define INTAKE_H_

#include "../Macros.h"

class Intake
{
public:
	Intake();
	~Intake();

	void setIntakeMotor(float speed);
	void toggleIntake(bool intakeButton, bool outtakeButton);
	void pivotIntake(float pivotSpeed);
	void setAngle(bool lockPivot);
	int getIntakeEncoderValue();

private:
	CANTalon* intakeRollerMotor;
	CANTalon* pivotMotor;

	bool intakeInwards;
};

#endif
