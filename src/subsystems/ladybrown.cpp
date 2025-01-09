#include "robot/ladybrown.h"

#include "globals.h"
#include "pros/motors.h"

#define SLOWER_VELOCITY 125
#define FASTER_VELOCITY 150

using namespace Robot;
using namespace Robot::Globals;

LadyBrown::LadyBrown(double kiP, double kiI, double kiD) {
   LadyBrownMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
   LadyBrown::kP = kiP;
   LadyBrown::kI = kiI;
   LadyBrown::kD = kiD;
}

LadyBrown::LadyBrown() {
   LadyBrownMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
   LadyBrown::kP = 0;
   LadyBrown::kI = 0;
   LadyBrown::kD = 0;
}

void LadyBrown::run() {

   if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      LadyBrownMotor.move_velocity(-SLOWER_VELOCITY);
   } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      LadyBrownMotor.move_velocity(SLOWER_VELOCITY);
   } else {
      LadyBrownMotor.brake();
   }
}

void LadyBrown::toggle() {}

// Vision sensor only works with LadyBrown, therefore it should not on
double LadyBrown::pid_update() { return 0; }