#include "robot/ladybrown.h"
#include <cstdlib>
#include <iostream>

#include "globals.h"
#include "lemlib/pid.hpp"
#include "pros/motors.h"

constexpr int SLOWER_VELOCITY = 125;
constexpr int FASTER_VELOCITY = 150;

constexpr double base_location = 0;
constexpr double load_location = -25.58;
constexpr double attack_location = -200;

using namespace Robot;
using namespace Robot::Globals;

LadyBrown::LADYBROWN_STATE current_state = Robot::LadyBrown::BASE_STATE;

LadyBrown::LadyBrown() {
   LadyBrownRotation.set_position(0);
}

void LadyBrown::run() {
   if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
      pros::Task task([&]() { MoveToPoint(); });
   } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
      pros::Task task([&]() { MoveToPoint(); });
   }
}

void LadyBrown::MoveToPoint(LadyBrown::LADYBROWN_STATE state) {
   lemlib::PID MoveToPointPID(1, 0, 0, 2, false);

   target = LadyBrownRotation.get_position();

   if (state == BASE_STATE) {
      target = 0;
   } else if (state == LOAD_STATE) {
      target = -2558;
   } else if (state == ATTACK_STATE) {
      target = -20000;
   }

   std::cout << "Before loop" << std::endl;
   std::cout << target << std::endl;

   while (true) {
      double error = target - LadyBrownRotation.get_position();
      
      double motor_voltage = MoveToPointPID.update(error);
      std::cout << motor_voltage << std::endl;

      if (std::abs(error) < 10) {
         LadyBrownMotor.brake();
         break;
      }

      LadyBrownMotor.move_voltage(motor_voltage);
      pros::delay(20);

   }

}
