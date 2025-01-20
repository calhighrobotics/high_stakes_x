#include "robot/auton.h"
#include "globals.h"
#include "lemlib/chassis/chassis.hpp"
#include "main.h" // IWYU pragma: export
#include "pros/motors.h"
#include "pros/rtos.hpp"


using namespace Robot;
using namespace Robot::Globals;

Autonomous::AUTON_ROUTINE Autonomous::auton = RED_LEFT;
std::string Autonomous::autonName;

constexpr int delay_constant = 1050;

// Red Left
void Autonomous::Auton1(Intake &intake, Latch &latch, DistanceSensor &distance) {
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   chassis.setPose(0, 0,0);
   // Move to first stake, then a bit farther at a slower speed for alignment
   chassis.moveToPoint(0, -27, 1400, {.forwards = false, .maxSpeed = 60},true);
   chassis.moveToPoint(0, -35, 1050, {.forwards = false, .maxSpeed = 30},true);
   chassis.waitUntilDone();
   pros::delay(200);
   // Grab the closest MOGO mech
   latch.toggle();
   // Load the ring onto the stake
   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(200);
   pros::delay(5000);
   
}
// Red Right
void Autonomous::Auton2(Intake &intake, Latch &latch, DistanceSensor &distance) {
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   chassis.setPose(0, 0,0);
   // Move to first stake, then a bit farther at a slower speed for alignment
   chassis.moveToPoint(0, -27, 1400, {.forwards = false, .maxSpeed = 60},true);
   chassis.moveToPoint(0, -35, 1050, {.forwards = false, .maxSpeed = 30},true);
   chassis.waitUntilDone();
   pros::delay(200);
   // Grab the closest MOGO mech
   latch.toggle();
   // Load the ring onto the stake
   IntakeMotor.move_relative(2200, 600);
   HookMotor.move_relative(2200, 200);
   pros::delay(300);
   chassis.setPose(0, 0, 0);
   // Point at the blue left side bottom ring for scoring
   chassis.turnToHeading(-75, 1000, {.direction=AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 70}, true);
   chassis.waitUntilDone();
   chassis.setPose(0, 0, 0);
   // Start the intake and hook for the rest of auton
   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(200);
   // Move to and back from the blue low ring
   chassis.moveToPoint(0, 22, 1250, {.forwards = true, .maxSpeed = 70},true);
   chassis.moveToPoint(0, -5, 1250, {.forwards = false, .maxSpeed = 90},true);
   chassis.waitUntilDone();
   // Turn to ladder cone
   chassis.turnToHeading(180, 2000);
   chassis.moveToPoint(0, -21, 1250, {.forwards = true, .maxSpeed = 50},true);
}

// Blue left
void Autonomous::Auton3(Intake &intake, Latch &latch, DistanceSensor &distance) {
      drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   chassis.setPose(0, 0,0);
   // Move to first stake, then a bit farther at a slower speed for alignment
   chassis.moveToPose(0, -28, 0, 2000, {.forwards = false});
   chassis.waitUntilDone();
   // Grab the closest MOGO mech
   latch.toggle();
   pros::delay(250);

   // Rotate toward blue ring
   chassis.turnToHeading(90, 1000);
   chassis.waitUntilDone();

   // Load the ring onto the stake
   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(200);

   // Moves to 2 ring stack
   chassis.setPose(0, 0, 0);
   chassis.moveToPoint(0, 25, 1250, {.forwards = true},true);
   chassis.turnToHeading(90, 1000);
   chassis.waitUntilDone();

   // Moves goal to corner
   chassis.setPose(0, 0, 0);
   chassis.moveToPose(0, -24, 0, 1250, {.forwards = false});
   chassis.waitUntilDone();
   latch.toggle();

   // Turn to ladder cone
   chassis.setPose(0, 0, 0);
   chassis.moveToPose(0, 29, 0,1250, {.forwards = true},true);
   chassis.turnToHeading(180, 1000);
   chassis.moveToPoint(0, 38,1000, {.forwards = false});
}

/*
 * @todo Flesh out this method before the competition in order to make it a full
 * solo awp autonomous. Blue right
 */
void Autonomous::Auton4(Intake &intake, Latch &latch, DistanceSensor &distance) {
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   chassis.setPose(0, 0,0);
   // Move to first stake, then a bit farther at a slower speed for alignment
   chassis.moveToPoint(0, -27, 1400, {.forwards = false, .maxSpeed = 60},true);
   chassis.moveToPoint(0, -35, 1050, {.forwards = false, .maxSpeed = 30},true);
   chassis.waitUntilDone();
   pros::delay(200);
   // Grab the closest MOGO mech
   latch.toggle();
   // Load the ring onto the stake
   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(200);
   pros::delay(5000);
}

// Skills
void Autonomous::Auton5(Intake &intake, Latch &latch, DistanceSensor &distance) {
   // Autonomous routine for the Skills challenge - 60 seconds MAX

   /* ##############################################*/
   //De-intake into alliance stake
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   IntakeMotor.move_relative(2200, 600);
   HookMotor.move_relative(2200, 200);
   pros::delay(1500);
   // ############################################## */

   //Move back into the center between the two stakes and point mogo at right stake
   /* ############################################## */
   chassis.setPose(0, 0, 0);
   chassis.moveToPoint(0, 15, 1400, {.forwards = true, .maxSpeed = 60}, true);
   chassis.turnToHeading(-90, 1000, {.direction=AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 70}, true);
   chassis.waitUntilDone();
   chassis.setPose(0, 0, 0);
   // ############################################## */

   //Move backwards into the stake
   /* ############################################## */
   chassis.moveToPoint(0, -25, 1400, {.forwards = false, .maxSpeed = 60},true);
   chassis.waitUntilDone();
   latch.toggle();
   pros::delay(750);
   // ############################################## */

   // Point to right rings and grab
   /* ############################################## */
   chassis.setPose(0, 0, 0);
   chassis.turnToHeading(180, 2000);
   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(200);
   chassis.setPose(0, 0,0);
   chassis.moveToPoint(0, 36, 1250, {.forwards = true, .maxSpeed = 70},true);
   chassis.setPose(0, 0, 0);
   chassis.turnToHeading(135, 2000);
   chassis.waitUntilDone();
   chassis.setPose(0, 0, 0);
   chassis.moveToPoint(0, 12, 1250, {.forwards = true, .maxSpeed = 70},true);
   chassis.turnToHeading(45, 2000);
   chassis.setPose(0, 0, 0);
   chassis.moveToPoint(0, -15, 1250, {.forwards = false, .maxSpeed = 70},true);
   latch.toggle();


}

// Takes in two parameters: The autonomous value as well as the puncher object.
void Autonomous::AutoDrive(Intake &intake, Latch &latch, DistanceSensor &distance) {
   // Keep the switcher running while the controller down button has not been pressed and the time period is not
   // autonomous Compare the current auton value to run the auton routine
   switch (Autonomous::auton) {
   case RED_LEFT:
      Auton1(intake, latch, distance);
      break;
   case RED_RIGHT:
      Auton2(intake, latch, distance);
      break;
   case BLUE_LEFT:
      Auton3(intake, latch, distance);
      break;
   case BLUE_RIGHT:
      Auton4(intake, latch, distance);
      break;
   case SKILLS:
      Auton5(intake, latch, distance);
      break;
   }
}

void Autonomous::AutonSwitcher(int autonNum) {
   switch (autonNum) {
   case 1:
      Autonomous::autonName = "Red Left";
      Autonomous::auton = RED_LEFT;
      break;
   case 2:
      Autonomous::autonName = "Red Right";
      Autonomous::auton = RED_RIGHT;
      break;
   case -1:
      Autonomous::autonName = "Blue Left";
      Autonomous::auton = BLUE_LEFT;
      break;
   case -2:
      Autonomous::autonName = "Blue Right";
      Autonomous::auton = BLUE_RIGHT;
      break;
   case 0:
      Autonomous::autonName = "Skills";
      Autonomous::auton = SKILLS;
   }
   std::cout << "Current auton: " + Autonomous::autonName << std::endl;
}