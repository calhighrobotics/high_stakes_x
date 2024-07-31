#include "robot/intake.h"

#include <cassert>

#include "globals.h"

using namespace Robot;
using namespace Robot::Globals;

Intake::Intake()
{
	elevated = false;
	alliance_color = false;
	controller.print(0, 0, "Intake initialized");
}

void Intake::score()
{
	IntakeMotor.move(127);
	async();
}

void Intake::run()
{
	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
		IntakeMotor.move(127);
	} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
		IntakeMotor.move(-127);
	} else {
		IntakeMotor.brake();
	}
}

void Intake::toggle()
{
	elevated = !elevated;
	IntakeToggle.toggle();
}

void Intake::eject() {

}

void Intake::async() {
	double color = colorSensor.get_hue();
	if (color > 200.0 && color < 230.0) { // blue
		if (alliance_color) {
			eject();
		}
		else {
			IntakeMotor.move(127);
		}
	} else if (color < 30.0 && color >= 0.0 || color > 330.0 && color <= 359.999) { // red
		if (alliance_color) {
			IntakeMotor.move(127);
		}
		else {
			eject();
		}
	} else {
		IntakeMotor.brake();
	}
}