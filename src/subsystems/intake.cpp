#include "robot/intake.h"

#include <cassert>

#include "globals.h"

using namespace Robot;
using namespace Robot::Globals;

Intake::Intake() {
    elevated = false;
    controller.print(0, 0, "Intake initialized");
}

void Intake::score() {
  IntakeMotor.move(127);
  pros::delay(3000);  // will modify later, will run until color sensor doesn't
                      // detect a ring
}

void Intake::run() {
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
    IntakeMotor.move(127);
  } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
    IntakeMotor.move(-127);
  } else {
    IntakeMotor.brake();
  }
}

void Intake::toggle() {
    !elevated;
    IntakeToggle.toggle();
}

/*void Intake::async() {
    std::assert(colorSensor.get_hue());
    
    
}*/