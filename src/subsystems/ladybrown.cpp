#include "robot/ladybrown.h"

#include "globals.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"

#define SLOWER_VELOCITY 125
#define FASTER_VELOCITY 150

using namespace Robot;
using namespace Robot::Globals;

bool LadyBrown::needs_warning = false;

LadyBrown::LadyBrown(double kiP, double kiI, double kiD) {
   LadyBrownMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
   LadyBrownMotor.set_zero_position(LadyBrownMotor.get_position());
   LadyBrown::needs_warning = false;
   LadyBrown::kP = kiP;
   LadyBrown::kI = kiI;
   LadyBrown::kD = kiD;
}

LadyBrown::LadyBrown() {
   LadyBrownMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
   LadyBrownMotor.set_zero_position(LadyBrownMotor.get_position());
   LadyBrown::needs_warning = false;
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
      if (!LadyBrown::needs_warning) {
         LadyBrownMotor.brake();
      }
   }
}

void LadyBrown::edge_check(void *param) {
   constexpr int TASK_DELAY_MILLIS = 100;
   constexpr int CONTROLLER_DELAY_MILLIS = 50;
   uint32_t time = pros::millis();
   LadyBrown::needs_warning = false;
   // Check if the lady brown position is too low
   while (true) {

      if (LadyBrownMotor.get_position() < -5 || LadyBrownMotor.get_position() >= 800) {
         while (LadyBrownMotor.get_position() < -5) {
            LadyBrown::needs_warning = true;
            controller.rumble(".");
         }
         while (LadyBrownMotor.get_position() >= 800) {
            LadyBrown::needs_warning = true;
            controller.rumble("-");
         }
      }
      LadyBrown::needs_warning = false;
      pros::Task::delay_until(&time, TASK_DELAY_MILLIS);
   }
}

void LadyBrown::toggle() {}

// Vision sensor only works with LadyBrown, therefore it should not on
double LadyBrown::pid_update() { return 0; }