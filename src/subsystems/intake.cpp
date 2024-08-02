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

void Intake::score() {
	double color = colorSensor.get_hue();
	bool red = color < 30.0 && color >= 0.0 || color > 330.0 && color <= 359.999;
	bool blue = color > 200.0 && color < 230.0;
	while (blue || red) {
		color = colorSensor.get_hue();
		red = color < 30.0 && color >= 0.0 || color > 330.0 && color <= 359.999;
		blue = color > 200.0 && color < 230.0;
		if (blue) {
			if (alliance_color) {
				IntakeMotor.move(-127);
			}
			else {
				IntakeMotor.move(127);
			}
		} else if (red) {
			if (alliance_color) {
				IntakeMotor.move(127);
			}
			else {
				IntakeMotor.move(-127);
			}
		} else {
			IntakeMotor.brake();
			break;
		}
		pros::delay(10);
	}
}