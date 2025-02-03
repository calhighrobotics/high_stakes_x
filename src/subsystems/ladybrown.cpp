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
   int location = 1;

   if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
      if (location <= 3) {
         location++;
         current_state = static_cast<LADYBROWN_STATE>(location);
         pros::Task task([&]() { MoveToPoint(); });
      }
   } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
      if (location >= 1) {
         location--;
         current_state = static_cast<LADYBROWN_STATE>(location);
         pros::Task task([&]() { MoveToPoint(); });
      }
   } else {
      LadyBrownMotor.move_velocity(0);
   }
}

void LadyBrown::MoveToPoint() {
   lemlib::PID MoveToPointPID(3, 2, 1, 2, false);

   target = LadyBrownRotation.get_position();
   
   if (current_state == BASE_STATE) {
      target = 0;
   } else if (current_state == LOAD_STATE) {
      target = -25.58;
   } else if (current_state == ATTACK_STATE) {
      target = -200;
   }

   while (true) {
      double error = target - LadyBrownRotation.get_position();
      
      double motor_voltage = MoveToPointPID.update(error);
      
      if (std::abs(error < 10)) {
         LadyBrownMotor.brake();
         break;
      }

      LadyBrownMotor.move_voltage(motor_voltage);
      pros::delay(20);

   }

}
