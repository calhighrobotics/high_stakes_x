#include "robot/intake.h"

#include "globals.h"

constexpr int SLOWER_VELOCITY = 200;
constexpr int FASTER_VELOCITY = 600;
constexpr int ONE_ROTATION = 835;

using namespace Robot;
using namespace Robot::Globals;

Intake::Intake() {
   elevated = false;
   alliance_color = false;
}

void Intake::run() {
   if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      IntakeMotor.move_velocity(-FASTER_VELOCITY);
   } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      IntakeMotor.move_velocity(FASTER_VELOCITY);
      spinHook();
   } else {
      IntakeMotor.brake();
   }
}

void Intake::toggle() { elevated = !elevated; }

void Intake::spinHook() {
   if (hookSwitch.get_value() && HookMotor.get_actual_velocity() == 0) {
      HookMotor.move_relative(ONE_ROTATION, -SLOWER_VELOCITY);
   }
}

// Vision sensor only works with intake, therefore it should not on
void Intake::checkStop() {}
