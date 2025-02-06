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

using namespace Robot;
using namespace Robot::Globals;

Autonomous::AUTON_ROUTINE Autonomous::auton = RED_LEFT;
std::string Autonomous::autonName;

constexpr int delay_constant = 1050;

// Red Left
void Autonomous::RedNeg(Intake &intake, Latch &latch, DistanceSensor &distance) {
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   chassis.setPose(0, 0, 0);
   // Move to first stake, then a bit farther at a slower speed for alignment
   chassis.moveToPoint(0, -27, 1400, {.forwards = false, .maxSpeed = 60}, true);
   chassis.moveToPoint(0, -35, 1050, {.forwards = false, .maxSpeed = 30}, true);
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
void Autonomous::RedPos(Intake &intake, Latch &latch, DistanceSensor &distance) {
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   chassis.setPose(0, 0, 0);
   // Move to first stake, then a bit farther at a slower speed for alignment
   chassis.moveToPoint(0, -27, 1400, {.forwards = false, .maxSpeed = 60}, true);
   chassis.moveToPoint(0, -35, 1050, {.forwards = false, .maxSpeed = 30}, true);
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
   chassis.turnToHeading(-75, 1000, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 70}, true);
   chassis.waitUntilDone();
   chassis.setPose(0, 0, 0);
   // Start the intake and hook for the rest of auton
   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(200);
   // Move to and back from the blue low ring
   chassis.moveToPoint(0, 22, 1250, {.forwards = true, .maxSpeed = 70}, true);
   chassis.moveToPoint(0, -5, 1250, {.forwards = false, .maxSpeed = 90}, true);
   chassis.waitUntilDone();
   // Turn to ladder cone
   chassis.turnToHeading(180, 2000);
   chassis.moveToPoint(0, -21, 1250, {.forwards = true, .maxSpeed = 50}, true);
}

// Blue left
void Autonomous::BluePos(Intake &intake, Latch &latch, Sweeper &sweeper, DistanceSensor &distance) {
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   chassis.setPose(0, 0, 0);

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
   sweeper.toggle();
   chassis.moveToPoint(35, 7, 1500);
   chassis.waitUntilDone();
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   chassis.moveToPose(25, -4, 170, 2000, {.horizontalDrift = 2});
   chassis.moveToPoint(32, 10, 1000, {.forwards = false});
   chassis.waitUntilDone();
   latch.toggle();
   // chassis.turnToHeading(180, 1000, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE});

   //// Moves goal to corner
   // chassis.moveToPoint(28, 3, 1250, {.forwards = false});
   // chassis.waitUntilDone();
   // latch.toggle();

   //// Turn to ladder cone
   // chassis.moveToPoint(25, -30, 1500, {.forwards = true},true);
   // chassis.turnToPoint(25, -40, 1000, {.forwards = false});
   // chassis.moveToPoint(25, -38,1000, {.forwards = false});
}

/*
 * @todo Flesh out this method before the competition in order to make it a full
 * solo awp autonomous. Blue right
 */
void Autonomous::BlueNeg(Intake &intake, Latch &latch, DistanceSensor &distance) {
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   chassis.setPose(0, 0, 0);
   // Move to first stake, then a bit farther at a slower speed for alignment
   chassis.moveToPoint(0, -27, 1400, {.forwards = false, .maxSpeed = 60}, true);
   chassis.moveToPoint(0, -35, 1050, {.forwards = false, .maxSpeed = 30}, true);
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
void Autonomous::Skills(Intake &intake, Latch &latch, DistanceSensor &distance, LadyBrown &ladybrown) {
   
   // Set pre-constants 
   HookMotor.set_zero_position(HookMotor.get_position());
   colorSensor.set_led_pwm(70);
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   chassis.setPose(0, 0, 0);

   // Autonomous routine for the Skills challenge - 60 seconds MAX
   /* ##############################################*/

   // De-hook into the alliance stake
   HookMotor.move_relative(200, 100);
   pros::delay(750);

   //Move to the center, then turn to and touch the right side Mogo.
   chassis.moveToPoint(0, 14, 1000);
   chassis.turnToPoint(19, 15, 1000, {.forwards = false});
   chassis.moveToPoint(17, 15, 1000, {.forwards = false, .earlyExitRange=2}, false);
   chassis.moveToPoint(19, 15, 1000, {.forwards = false}, false);

   //Latch the mogo - delays just in case
   LatchControl.extend();
   pros::delay(250);

   //Turn to the above ring - Start intake and hook, and move there
   chassis.turnToPoint(24, 38.75, 1000, {}, false);
   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(150);
   chassis.moveToPoint(24, 38.75, 2000);

   // Immediately move to the farthest ring. A couple of tasks happen while this is going on
   chassis.moveToPose(48, 88.5, 0, 3000, {.horizontalDrift = 8, .lead = 0.4}, true);
   //Checks between 10-45 inches of movement for if the hook got stuck on the 
   for (int i = 10; i<45; i++) {
   chassis.waitUntil(i);
   std::cout << "velocity" << HookMotor.get_actual_velocity() << std::endl;
   if (HookMotor.get_actual_velocity() < 25) {
      HookMotor.move_velocity(-);
      HookMotor.move_velocity(100);
   }

   if (i == 40) {
      ladybrown.MoveToPoint(LadyBrown::LOAD_STATE);

   }
   }

   HookMotor.move_velocity(100);
   chassis.waitUntilDone();
   //std::cout << "velocity" << HookMotor.get_actual_velocity() << std::endl;
   chassis.turnToPoint(40, 62.5, 800, {.forwards=false});

   if (HookMotor.get_actual_velocity() < 25) {
      HookMotor.move_relative(-50, 200);
      HookMotor.move_velocity(100);
   }

   chassis.moveToPoint(40, 62.5, 1500, {.forwards=false}, true);

   HookMotor.move_relative(-20, 200);
   HookMotor.move_velocity(100);


   chassis.waitUntil(20);
   HookMotor.brake();

   chassis.waitUntilDone();

   chassis.turnToPoint(78, 62.5, 1000);

   chassis.moveToPoint(72, 62.5, 2000, {.forwards=true, .maxSpeed=50}, true);

   chassis.waitUntil(18);
   IntakeMotor.brake();

   chassis.waitUntilDone();

   pros::delay(500);
   ladybrown.MoveToPoint(LadyBrown::ATTACK_STATE);

   chassis.moveToPoint(47, 62.5, 1500, {.forwards = false, .maxSpeed = 75});
   chassis.waitUntil(15);
   IntakeMotor.move_velocity(600);
   chassis.turnToPoint(47, 0, 1000);

   ladybrown.MoveToPoint(LadyBrown::BASE_STATE);

   chassis.moveToPoint(47, 6, 2000, {.forwards = true, .maxSpeed = 55, .earlyExitRange=4.5});

   HookMotor.move(125);

   chassis.waitUntil(20);

   for (int i = 5; i<47; i++) {
   chassis.waitUntil(i);
   std::cout << "velocity" << HookMotor.get_actual_velocity() << std::endl;
   if (HookMotor.get_actual_velocity() < 25) {
      HookMotor.move_relative(-50, 200);
      HookMotor.move_velocity(100);
   }
   }

   chassis.waitUntilDone();
   pros::delay(2000);

   ladybrown.MoveToPoint(LadyBrown::BASE_STATE);

   chassis.turnToPoint(62, 17, 1000);
   chassis.moveToPoint(62, 17, 2000, {.forwards = true, .maxSpeed = 50, .earlyExitRange=4});

   chassis.turnToHeading(-30, 1000, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE}, false);

   chassis.moveToPoint(64, 10, 1000, {.forwards = false, .maxSpeed = 50, .earlyExitRange=1.5}, false);
   pros::delay(1300);
   LatchControl.retract();

   IntakeMotor.brake();
   HookMotor.brake();

   chassis.moveToPose(48, 15, -90, 1050, {.forwards = true, .maxSpeed = 80}, true);




}

// Takes in two parameters: The autonomous value as well as the puncher object.
void Autonomous::AutoDrive(Intake &intake, Latch &latch, Sweeper &sweeper, DistanceSensor &distance,
                           LadyBrown &ladybrown) {
   // Keep the switcher running while the controller down button has not been pressed and the time period is not
   // autonomous Compare the current auton value to run the auton routine
   switch (Autonomous::auton) {
   case RED_LEFT:
      RedNeg(intake, latch, distance);
      break;
   case RED_RIGHT:
      RedPos(intake, latch, distance);
      break;
   case BLUE_LEFT:
      BluePos(intake, latch, sweeper, distance);
      break;
   case BLUE_RIGHT:
      BlueNeg(intake, latch, distance);
      break;
   case SKILLS:
      Skills(intake, latch, distance, ladybrown);
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