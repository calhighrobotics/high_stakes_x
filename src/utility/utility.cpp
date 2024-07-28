#include "robot/utility.h"

#include "globals.h"

using namespace Robot;
using namespace Robot::Globals;
/**
 * \todo Figure out a way to send an event to the different objects to toggle
 * between the different subsystems.
 */

void Utility::displayMotorVel() {
  // std::vector<std::int32_t> currents = drive_.get_current_draws();// get the
  // current position of the robot
  pros::lcd::print(0, "Motor velocity draw", 0);
  pros::lcd::print(1, "motor 2 vel: %lf", LeftFront.get_actual_velocity());
  pros::lcd::print(2, "motor 2 vel: %lf", RightFront.get_actual_velocity());
  pros::lcd::print(3, "motor 3 vel: %lf", LeftMid.get_actual_velocity());
  pros::lcd::print(4, "motor 4 vel: %lf", RightMid.get_actual_velocity());
  pros::lcd::print(5, "motor 5 vel: %lf", LeftBack.get_actual_velocity());
  pros::lcd::print(
      6, "motor 6 vel: %lf",
      RightBack
          .get_actual_velocity());  // print the x position// print the heading
}

void Utility::displayLocation() {
  using namespace Robot::Globals;

  lemlib::Pose pose =
      chassis.getPose();  // get the current position of the robot
  pros::lcd::print(0, "x: %f", pose.x);            // print the x position
  pros::lcd::print(1, "y: %f", pose.y);            // pri∟nt the y position
  pros::lcd::print(2, "heading: %f", pose.theta);  // print the heading
}
