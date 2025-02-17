#include "robot/auton.h"
#include "globals.h"
#include "lemlib/chassis/chassis.hpp"
#include "main.h" // IWYU pragma: export
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "robot/intake.h"
#include "robot/ladybrown.h"
#include "robot/sweeper.h"
#include <iostream>
#include <string>

using namespace Robot;
using namespace Robot::Globals;

Autonomous::AUTON_ROUTINE Autonomous::auton = RED_POS;
std::string Autonomous::autonName = "Red Positive";

constexpr int delay_constant = 1050;

// Red Left
void Autonomous::RedNeg(Intake &intake, Latch &latch, DistanceSensor &distance) {
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   chassis.setPose(0, 0, 0);

   
   chassis.moveToPoint(0, -18, 2000, {.forwards = false});
   chassis.moveToPoint(0, -24, 2000, {.forwards = false, .maxSpeed=60}, false);

   latch.toggle();

   chassis.turnToHeading(90, 1000);
   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(200);

   chassis.moveToPoint(27, -24, 1500);

   chassis.waitUntilDone();
   pros::delay(1000);
   
   chassis.turnToHeading(-90.0, 1000);
   chassis.moveToPoint(-24, 20, 1500, {.maxSpeed=60});
   
}
// Red Right
void Autonomous::RedPos(Intake &intake, Latch &latch, Sweeper &sweeper, DistanceSensor &distance, LadyBrown &ladybrown) {
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   chassis.setPose(0, 0,0);

   // Move to first stake
   chassis.moveToPose(0, -28, 0, 2000, {.forwards = false});
   chassis.waitUntilDone();
   // Grab the closest MOGO mech
   latch.toggle();
   pros::delay(250);

   // Rotate toward blue ring
   chassis.turnToPoint(-25, -27, 1000);
   chassis.waitUntilDone();

   // Load the ring onto the stake
   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(200);

   // Moves to 2 ring stack

   chassis.moveToPoint(-25, -27, 1250, {.forwards = true});
   chassis.turnToPoint(-33.5, 6, 1000);
   SweeperControl.extend();
   chassis.moveToPoint(-35, 7, 1500);
   chassis.waitUntilDone();
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   chassis.moveToPose(-25, -4, 170, 2000, {.horizontalDrift = 2});
   chassis.moveToPoint(-32, 10, 1000, {.forwards = false});
   chassis.waitUntilDone();
   latch.toggle();

   chassis.turnToPoint(14, -36, 800);
   SweeperControl.retract();
   ladybrown.MoveToPoint(LadyBrown::LOAD_STATE);

   chassis.moveToPoint(14, -36, 5000);
}

// Blue left
void Autonomous::BluePos(Intake &intake, Latch &latch, Sweeper &sweeper, DistanceSensor &distance, LadyBrown &ladybrown) {

   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   chassis.setPose(0, 0,0);

   // Move to first stake
   chassis.moveToPose(0, -28, 0, 2000, {.forwards = false});
   chassis.waitUntilDone();
   // Grab the closest MOGO mech
   latch.toggle();
   pros::delay(250);

   // Rotate toward blue ring
   chassis.turnToPoint(25, -27, 1000);
   chassis.waitUntilDone();

   // Load the ring onto the stake
   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(200);

   // Moves to 2 ring stack

   chassis.moveToPoint(25, -27, 1250, {.forwards = true});
   chassis.turnToPoint(33.5, 6, 1000);
   SweeperControl.extend();
   chassis.moveToPoint(35, 7, 1500);
   chassis.waitUntilDone();
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   chassis.moveToPose(25, -4, 170, 2000, {.horizontalDrift = 2});
   chassis.moveToPoint(32, 10, 1000, {.forwards = false});
   chassis.waitUntilDone();
   latch.toggle();

   chassis.turnToPoint(-14, -36, 800);
   SweeperControl.retract();
   ladybrown.MoveToPoint(LadyBrown::LOAD_STATE);

   chassis.moveToPoint(-14, -36, 5000);

}

void Autonomous::BluePosLateGoalRush(Intake &intake, Latch &latch, Sweeper &sweeper, DistanceSensor &distance, LadyBrown &ladybrown) {
      // drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   // chassis.setPose(-36, 11,-17);

   // IntakeMotor.move_velocity(600);
   // chassis.moveToPoint(-49, 38.5, 1100, {.minSpeed=60}, false);
   // chassis.moveToPose(-47, 47, -5, 1000, {.horizontalDrift=8, .earlyExitRange=2}, true);


   // chassis.waitUntil(37);
   // SweeperControl.extend();

   // chassis.waitUntilDone();

   // pros::delay(200);

   // chassis.moveToPoint(-48, 8, 1500, {.forwards=false, .maxSpeed=90}, false);

   // SweeperControl.retract();

   // chassis.turnToPoint(-24, 38.5, 750, {.forwards=false});
   // chassis.moveToPoint(-24, 38.5, 1100, {.forwards=false, .maxSpeed=65});
   // chassis.moveToPoint(-22, 40.5, 550, {.forwards=false, .maxSpeed=50});

   // LatchControl.extend();

   // chassis.turnToPoint(-24, 4, 600, {.forwards=true});
   // chassis.moveToPoint(-24, 4, 1200, {.maxSpeed=90});
   // chassis.waitUntil(8);
   // HookMotor.move_velocity(200);

   // chassis.turnToPoint(-12, 45, 1100, {.forwards=true}, false);

   // chassis.moveToPoint(-12, 45, 1150, {.maxSpeed=60});

   // chassis.turnToHeading(90, 650);

   // SweeperControl.extend();
   
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   chassis.setPose(0, 0,0);

   // Move to first stake
   chassis.moveToPose(0, -28, 0, 2000, {.forwards = false});
   chassis.waitUntilDone();
   // Grab the closest MOGO mech
   latch.toggle();
   pros::delay(250);

   // Rotate toward blue ring
   chassis.turnToPoint(25, -27, 1000);
   chassis.waitUntilDone();

   // Load the ring onto the stake
   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(200);

   // Moves to 2 ring stack
   chassis.moveToPoint(25, -27, 1250, {.forwards = true});
   chassis.turnToPoint(25, 0, 1000, {.forwards = false});
   chassis.waitUntilDone();

   // Moves goal to corner
   chassis.moveToPoint(28, 3, 1250, {.forwards = false});
   chassis.waitUntilDone();

   HookMotor.brake();
   latch.toggle();

   // Move to Third goal
   chassis.moveToPoint(25, -30, 1500, {.forwards = true},true);
   chassis.turnToPoint(25, -40, 1000, {.forwards = false});
   chassis.moveToPoint(25, -38,1000, {.forwards = false});
}

void Autonomous::RedPosLateGoalRush(Intake &intake, Latch &latch, Sweeper &sweeper, DistanceSensor &distance, LadyBrown &ladybrown) {
      // drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   // chassis.setPose(-36, 11,-17);

   // IntakeMotor.move_velocity(600);
   // chassis.moveToPoint(-49, 38.5, 1100, {.minSpeed=60}, false);
   // chassis.moveToPose(-47, 47, -5, 1000, {.horizontalDrift=8, .earlyExitRange=2}, true);


   // chassis.waitUntil(37);
   // SweeperControl.extend();

   // chassis.waitUntilDone();

   // pros::delay(200);

   // chassis.moveToPoint(-48, 8, 1500, {.forwards=false, .maxSpeed=90}, false);

   // SweeperControl.retract();

   // chassis.turnToPoint(-24, 38.5, 750, {.forwards=false});
   // chassis.moveToPoint(-24, 38.5, 1100, {.forwards=false, .maxSpeed=65});
   // chassis.moveToPoint(-22, 40.5, 550, {.forwards=false, .maxSpeed=50});

   // LatchControl.extend();

   // chassis.turnToPoint(-24, 4, 600, {.forwards=true});
   // chassis.moveToPoint(-24, 4, 1200, {.maxSpeed=90});
   // chassis.waitUntil(8);
   // HookMotor.move_velocity(200);

   // chassis.turnToPoint(-12, 45, 1100, {.forwards=true}, false);

   // chassis.moveToPoint(-12, 45, 1150, {.maxSpeed=60});

   // chassis.turnToHeading(90, 650);

   // SweeperControl.extend();
   
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   chassis.setPose(0, 0,0);

   // Move to first stake
   chassis.moveToPose(0, -28, 0, 2000, {.forwards = false});
   chassis.waitUntilDone();
   // Grab the closest MOGO mech
   latch.toggle();
   pros::delay(250);

   // Rotate toward blue ring
   chassis.turnToPoint(-25, -27, 1000);
   chassis.waitUntilDone();

   // Load the ring onto the stake
   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(200);

   // Moves to 2 ring stack
   chassis.moveToPoint(-25, -27, 1250, {.forwards = true});
   chassis.turnToPoint(-25, 0, 1000, {.forwards = false});
   chassis.waitUntilDone();

   // Moves goal to corner
   chassis.moveToPoint(-28, 3, 1250, {.forwards = false});
   chassis.waitUntilDone();
   HookMotor.brake();
   latch.toggle();

   // Move to Third goal
   chassis.moveToPoint(-25, -30, 1500, {.forwards = true},true);
   chassis.turnToPoint(-25, -40, 1000, {.forwards = false});
   chassis.moveToPoint(-25, -38,1000, {.forwards = false});
}

/*
 * @todo Flesh out this method before the competition in order to make it a full
 * solo awp autonomous. Blue right
 */
void Autonomous::BlueNeg(Intake &intake, Latch &latch, DistanceSensor &distance) {
   // drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   // chassis.setPose(0, 0, 0);
   // // Move to first stake, then a bit farther at a slower speed for alignment
   // chassis.moveToPoint(0, -27, 1800, {.forwards = false, .maxSpeed = 60}, true);
   // chassis.moveToPoint(0, -35, 2050, {.forwards = false, .maxSpeed = 30}, true);
   // chassis.waitUntilDone();
   // pros::delay(500);
   // // Grab the closest MOGO mech
   // LatchControl.extend();
   // pros::delay(2000);
   // // Load the ring onto the stake
   // IntakeMotor.move_velocity(600);
   // HookMotor.move_velocity(200);
   // pros::delay(3000);
   
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   chassis.setPose(0, 0, 0);

   
   chassis.moveToPoint(0, -18, 2000, {.forwards = false});
   chassis.moveToPoint(0, -24, 2000, {.forwards = false, .maxSpeed=60}, false);

   latch.toggle();

   chassis.turnToHeading(-90, 1000);
   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(200);

   chassis.moveToPoint(-27, -24, 1500);

   chassis.waitUntilDone();
   pros::delay(1000);
   
   chassis.turnToHeading(90.0, 1000);
   chassis.moveToPoint(24, 20, 1500, {.maxSpeed=60});
 

}

// Takes in two parameters: The autonomous value as well as the puncher object.
void Autonomous::AutoDrive(Intake &intake, Latch &latch, Sweeper &sweeper, DistanceSensor &distance,
                           LadyBrown &ladybrown) {
   // Keep the switcher running while the controller down button has not been pressed and the time period is not
   // autonomous Compare the current auton value to run the auton routine
   switch (Autonomous::auton) {
   case RED_NEG:
      Autonomous::autonName = "Red Negative";
      RedNeg(intake, latch, distance);
      break;
   case RED_POS:
      Autonomous::autonName = "Red Positive";
      RedPos(intake, latch, sweeper, distance, ladybrown);
      break;
   case RED_POS_LATE_RUSH:
      Autonomous::autonName = "Red Positive Late Rush";
      RedPosLateGoalRush(intake, latch, sweeper, distance, ladybrown);
      break;
   case BLUE_POS:
      Autonomous::autonName = "Blue Positive";
      BluePos(intake, latch, sweeper, distance, ladybrown);
      break;
   case BLUE_NEG:
      Autonomous::autonName = "Blue Negative";
      BlueNeg(intake, latch, distance);
      break;
   case BLUE_POS_LATE_RUSH:
      Autonomous::autonName = "Blue Positive Late Rush";
      BluePosLateGoalRush(intake, latch, sweeper, distance, ladybrown);
      break;
   case SKILLS:
      Autonomous::autonName = "Skills";
      Skills(intake, latch, distance, ladybrown);
      break;
   }
}

void Autonomous::AutonSwitcher(int autonNum) {
   switch (autonNum) {
   case 1:
      Autonomous::autonName = "Red Negative";
      Autonomous::auton = RED_NEG;
      break;
   case 2:
      Autonomous::autonName = "Red Positive Sweep";
      Autonomous::auton = RED_POS;
      break;
   case 3:
      Autonomous::autonName = "Red Positive Late Rush";
      Autonomous::auton = RED_POS_LATE_RUSH;
      break;
   case -1:
      Autonomous::autonName = "Blue Positive Sweep";
      Autonomous::auton = BLUE_POS;
      break;
   case -2:
      Autonomous::autonName = "Blue Positive Late Rush";
      Autonomous::auton = BLUE_POS_LATE_RUSH;
      break;
   case -3:
      Autonomous::autonName = "Blue Negative";
      Autonomous::auton = BLUE_NEG;
      break;
   case 0:
      Autonomous::autonName = "Skills";
      Autonomous::auton = SKILLS;
   }
   std::cout << "Current auton: " + Autonomous::autonName << std::endl;
}