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
void Autonomous::RedNeg(Intake &intake, Latch &latch, DistanceSensor &distance, LadyBrown &ladybrown) {

   //

   HookMotor.set_zero_position(HookMotor.get_position());
   colorSensor.set_led_pwm(70);
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   //Edge of lady brown is 5.5 inches from the alliance wall stake.
   chassis.setPose(0, 0, 112);
 
   ladybrown.MoveToPoint(LadyBrown::ATTACK_STATE, 150, 900);

   chassis.moveToPose(-11, 44, 180, 2000, {.forwards=false, .horizontalDrift=5.5});

   ladybrown.MoveToPoint(LadyBrown::BASE_STATE, 150, 1000);
   chassis.waitUntilDone();
   LatchControl.extend();
   pros::delay(250);
   chassis.swingToPoint(-28, 54.5, lemlib::DriveSide::RIGHT, 1500, { .direction=AngularDirection::CW_CLOCKWISE });

   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(200);
   chassis.moveToPoint(-28, 54.5, 5000);
   chassis.turnToPoint(-42, 55, 5000);

   chassis.moveToPoint(-42, 55, 2500, {.minSpeed = 75}, false);
   pros::delay(750);

   chassis.turnToPoint(-19, 40, 1000, {.forwards=false});
   chassis.moveToPoint(-19, 40, 1000, {.forwards=false});
   chassis.turnToPoint(-40, 39, 1000);
   chassis.moveToPoint(-40, 39, 1000);

   // chassis.turnToPoint(7.5, 39, 1000, {.direction=AngularDirection::CW_CLOCKWISE});
   // chassis.moveToPoint(7.5, 39, 7500, {.minSpeed=25, .earlyExitRange=15});
   // chassis.waitUntil(18);
   // IntakeMotor.brake();

   chassis.turnToPoint(9, 16.5, 1000, {.direction=AngularDirection::CW_CLOCKWISE});
   chassis.moveToPoint(9, 16.5, 7500, {.minSpeed=25, .earlyExitRange=15});
   chassis.waitUntil(13);
   IntakeLift.extend();

   // chassis.moveToPoint(9, 16.5, 7500, {.maxSpeed=25});
   
}

void RedNegBAK(Intake &intake, Latch &latch, DistanceSensor &distance, LadyBrown &ladybrown) {

   
   //IntakeMotor.brake();

   HookMotor.set_zero_position(HookMotor.get_position());
   colorSensor.set_led_pwm(70);
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   //Edge of lady brown is 5.5 inches from the alliance wall stake.
   chassis.setPose(0, 0, 112);
 
   ladybrown.MoveToPoint(LadyBrown::ATTACK_STATE, 150, 900);

   chassis.moveToPose(-11, 44, 180, 2000, {.forwards=false, .horizontalDrift=5.5});

   ladybrown.MoveToPoint(LadyBrown::BASE_STATE, 150, 1000);
   chassis.waitUntilDone();
   LatchControl.extend();
   pros::delay(250);
   chassis.swingToPoint(-28, 53.5, lemlib::DriveSide::RIGHT, 1500, {.direction=AngularDirection::CW_CLOCKWISE});

   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(200);
   chassis.moveToPoint(-28, 53.5, 5000);
   chassis.turnToPoint(-43, 54, 5000);

   chassis.moveToPoint(-43, 54, 2500, {.minSpeed = 65}, false);
   pros::delay(750);

   chassis.turnToPoint(-19, 40, 1000, {.forwards=false});
   chassis.moveToPoint(-19, 40, 1000, {.forwards=false});
   chassis.turnToPoint(-38, 39, 1000);
   chassis.moveToPoint(-38, 39, 1000);

   chassis.turnToPoint(9, 16.5, 1000, {.direction=AngularDirection::CW_CLOCKWISE});
   chassis.moveToPoint(9, 16.5, 7500, {.minSpeed=25, .earlyExitRange=15});
   chassis.waitUntil(10);
   IntakeLift.extend();

   chassis.moveToPoint(9, 16.5, 7500, {.maxSpeed=25});


}

// Red Right
void Autonomous::RedPos(Intake &intake, Latch &latch, Sweeper &sweeper, DistanceSensor &distance, LadyBrown &ladybrown) {

   bool elims = true;
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   chassis.setPose(0, 0,-12);
   chassis.moveToPoint(-14, 35, 2500, {.minSpeed=45, .earlyExitRange=2});
   IntakeMotor.move_velocity(600);
   chassis.waitUntilDone();
   //lesser angle due to doinker displacement
   chassis.turnToHeading(0, 300);
   SweeperControl.extend();
   //Use sin for the x, cos for the y
   chassis.moveToPoint(chassis.getPose().x-3.55, chassis.getPose().y-14, 2000, {.forwards=false, .minSpeed=25});
   chassis.waitUntilDone();
   SweeperControl.retract();
   pros::delay(250);
   // Same turn to the mogo
   chassis.turnToHeading(-170, 1000, {.direction=AngularDirection::CCW_COUNTERCLOCKWISE});
   std::cout << chassis.getPose().x << " + " << chassis.getPose().y << std::endl;
   std::cout << chassis.getPose().x << " + " << chassis.getPose().y+8 << std::endl;

   chassis.moveToPoint(chassis.getPose().x+8, chassis.getPose().y+21, 1500, {.forwards=false}, false);
   LatchControl.extend();
   pros::delay(750);

   std::cout << chassis.getPose().x << " + " << chassis.getPose().y << std::endl;
   
   //chassis.turnToPoint(29, -12, 750, {.forwards=false, .direction=AngularDirection::CCW_COUNTERCLOCKWISE});
   chassis.moveToPoint(-29, -12, 2500, {.forwards=true}, true);
   chassis.waitUntil(10);

   HookMotor.move_velocity(200);
   chassis.turnToPoint(-2, -14, 1000);
   chassis.waitUntilDone();

   LatchControl.retract();
   chassis.moveToPoint(-2, -14, 2500);
   HookMotor.move_velocity(0);

   pros::delay(250);
   chassis.moveToPose(-35, 28, -180, 2500, {.forwards=false, .lead=0.6}, false);

   LatchControl.extend();
   pros::delay(250);
   HookMotor.move_velocity(200);
   pros::delay(250);

   if (!elims) {
      chassis.moveToPose(-48, 38, -135, 2000, {.forwards=false, .horizontalDrift=5.5});
      chassis.waitUntil(6);
      HookMotor.move_velocity(0);
      pros::Task move([&]() { ladybrown.MoveToPoint(LadyBrown::LOAD_STATE); }, "LadyBrownMove");

   }
   else {
      pros::delay(150);
      chassis.moveToPoint(-3.5, -3, 1000, {.minSpeed=20, .earlyExitRange=10});
      chassis.waitUntil(4);
      IntakeMotor.move_velocity(0);
   }

}
// Red Sweep - PROBABLY NEVER RUN THIS
void RedPosBAK(Intake &intake, Latch &latch, Sweeper &sweeper, DistanceSensor &distance, LadyBrown &ladybrown) {
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


// Blue Goal Rush
void Autonomous::BluePos(Intake &intake, Latch &latch, Sweeper &sweeper, DistanceSensor &distance, LadyBrown &ladybrown) {
   bool elims = false;
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   chassis.setPose(0, 0,12);
   chassis.moveToPoint(7, 35, 2500, {.minSpeed=45, .earlyExitRange=2});
   IntakeMotor.move_velocity(600);
   chassis.waitUntilDone();
   chassis.turnToHeading(-17.5, 300);
   SweeperControl.extend();
   //Use sin for the x, cos for the y
   chassis.moveToPoint(chassis.getPose().x+3.55, chassis.getPose().y-14, 2000, {.forwards=false, .minSpeed=25});
   chassis.waitUntilDone();
   SweeperControl.retract();
   pros::delay(250);

   chassis.turnToHeading(-170, 1000, {.direction=AngularDirection::CCW_COUNTERCLOCKWISE});
   std::cout << chassis.getPose().x << " + " << chassis.getPose().y << std::endl;
   std::cout << chassis.getPose().x << " + " << chassis.getPose().y+8 << std::endl;

   chassis.moveToPoint(chassis.getPose().x, chassis.getPose().y+21, 1500, {.forwards=false}, false);
   LatchControl.extend();
   pros::delay(750);

   std::cout << chassis.getPose().x << " + " << chassis.getPose().y << std::endl;
   
   //chassis.turnToPoint(29, -12, 750, {.forwards=false, .direction=AngularDirection::CCW_COUNTERCLOCKWISE});
   chassis.moveToPoint(29, -12, 2500, {.forwards=true}, true);
   chassis.waitUntil(10);

   HookMotor.move_velocity(200);
   chassis.turnToPoint(4, -14, 1000);
   chassis.waitUntilDone();

   LatchControl.retract();
   chassis.moveToPoint(4, -14, 2500);
   HookMotor.move_velocity(0);

   pros::delay(250);
   chassis.moveToPose(35, 24, -180, 2500, {.forwards=false, .lead=0.6}, false);

   LatchControl.extend();
   pros::delay(250);
   HookMotor.move_velocity(200);
   pros::delay(250);

   if (!elims) {
      chassis.moveToPose(48, 38, -135, 2000, {.forwards=false, .horizontalDrift=5.5});
      chassis.waitUntil(6);
      HookMotor.move_velocity(0);
      pros::Task move([&]() { ladybrown.MoveToPoint(LadyBrown::LOAD_STATE); }, "LadyBrownMove");

   }
   else {
      pros::delay(150);
      chassis.moveToPoint(3.5, -3, 1000, {.minSpeed=20, .earlyExitRange=10});
      chassis.waitUntil(4);
      IntakeMotor.move_velocity(0);
   }


   //LatchControl.retract();

   // Move to first stake
   

}
// Blue sweep - PROBABLY NEVER RUN THIS
void BluePosBAK(Intake &intake, Latch &latch, Sweeper &sweeper, DistanceSensor &distance, LadyBrown &ladybrown) {

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
   // chassis.setPose(0, 0,0);

   // // Move to first stake
   // chassis.moveToPose(0, -28, 0, 2000, {.forwards = false});
   // chassis.waitUntilDone();
   // // Grab the closest MOGO mech
   // latch.toggle();
   // pros::delay(250);

   // // Rotate toward blue ring
   // chassis.turnToPoint(25, -27, 1000);
   // chassis.waitUntilDone();

   // // Load the ring onto the stake
   // IntakeMotor.move_velocity(600);
   // HookMotor.move_velocity(200);

   // // Moves to 2 ring stack
   // chassis.moveToPoint(25, -27, 1250, {.forwards = true});
   // chassis.turnToPoint(25, 0, 1000, {.forwards = false});
   // chassis.waitUntilDone();

   // // Moves goal to corner
   // chassis.moveToPoint(28, 3, 1250, {.forwards = false});
   // chassis.waitUntilDone();

   // HookMotor.brake();
   // latch.toggle();

   // // Move to Third goal
   // chassis.moveToPoint(25, -30, 1500, {.forwards = true},true);
   // chassis.turnToPoint(25, -40, 1000, {.forwards = false});
   // chassis.moveToPoint(25, -38,1000, {.forwards = false});


   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   //chassis.setPose(0, 0,0);

   chassis.setPose(12, -9, 112);
 
   ladybrown.MoveToPoint(LadyBrown::ATTACK_STATE, 150, 2000);

   chassis.moveToPose(0, 28, -180, 2000, {.forwards=false, .horizontalDrift=5.5});

   // Move to first stake
   //chassis.moveToPose(0, -28, 0, 2000, {.forwards = false});

   ladybrown.MoveToPoint(LadyBrown::BASE_STATE);
   chassis.waitUntilDone();
   // Grab the closest MOGO mech
   latch.toggle();
   pros::delay(250);

   // Rotate toward blue ring
   chassis.turnToPoint(-25, 27, 1000);
   chassis.waitUntilDone();

   // Load the ring onto the stake
   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(200);

   // Moves to 2 ring stack
   chassis.moveToPoint(-27, 27, 1250, {.forwards = true});
   chassis.turnToPoint(-19, 0, 1000, {.forwards = false});
   chassis.waitUntilDone();

   // Moves goal to corner
   chassis.moveToPoint(0, 18, 1250, {.forwards = false});
   chassis.waitUntilDone();
   HookMotor.brake();
   latch.toggle();

   // Move to Third goal
   chassis.moveToPoint(-25, 26, 1500, {.forwards = true},true);
   chassis.turnToPoint(-25, 36, 1000, {.forwards = false});
   chassis.moveToPoint(-25, 34,1000, {.forwards = false});
}

void Autonomous::RedPosLateGoalRush(Intake &intake, Latch &latch, Sweeper &sweeper, DistanceSensor &distance, LadyBrown &ladybrown) {
   
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   //chassis.setPose(0, 0,0);
   
   // Move to first stake
   // chassis.moveToPose(0, -28, 0, 2000, {.forwards = false});
   // chassis.waitUntilDone();
   // // Grab the closest MOGO mech
   // latch.toggle();
   // pros::delay(250);

   // // Rotate toward blue ring
   // chassis.turnToPoint(-25, -27, 1000);
   // chassis.waitUntilDone();

   // // Load the ring onto the stake
   // IntakeMotor.move_velocity(600);
   // HookMotor.move_velocity(200);

   // // Moves to 2 ring stack
   // chassis.moveToPoint(-25, -27, 1250, {.forwards = true});
   // chassis.turnToPoint(-25, 0, 1000, {.forwards = false});
   // chassis.waitUntilDone();

   // // Moves goal to corner
   // chassis.moveToPoint(-28, 3, 1250, {.forwards = false});
   // chassis.waitUntilDone();
   // HookMotor.brake();
   // latch.toggle();

   // // Move to Third goal
   // chassis.moveToPoint(-25, -30, 1500, {.forwards = true},true);
   // chassis.turnToPoint(-25, -40, 1000, {.forwards = false});
   // chassis.moveToPoint(-25, -38,1000, {.forwards = false});

   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   //chassis.setPose(0, 0,0);

   chassis.setPose(-12, -9, -112);
 
   ladybrown.MoveToPoint(LadyBrown::ATTACK_STATE, 150, 1000);

   chassis.moveToPose(0, 30, -180, 2000, {.forwards=false, .horizontalDrift=5.5});

   // Move to first stake
   //chassis.moveToPose(0, -28, 0, 2000, {.forwards = false});

   ladybrown.MoveToPoint(LadyBrown::BASE_STATE);
   chassis.waitUntilDone();
   // Grab the closest MOGO mech
   latch.toggle();
   pros::delay(250);

   // Rotate toward blue ring
   chassis.turnToPoint(25, 27, 1000);
   chassis.waitUntilDone();

   // Load the ring onto the stake
   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(200);

   // Moves to 2 ring stack
   chassis.moveToPoint(27, 27, 1250, {.forwards = true});
   chassis.turnToPoint(19, 0, 1000, {.forwards = false});
   chassis.waitUntilDone();

   // Moves goal to corner
   chassis.moveToPoint(10, -7, 1250, {.forwards = false});
   chassis.waitUntilDone();
   HookMotor.brake();
   latch.toggle();

   // Move to Third goal
   chassis.moveToPoint(25, 26, 1500, {.forwards = true},true);
   chassis.turnToPoint(25, 36, 1000, {.forwards = false});
   chassis.moveToPoint(25, 34,1000, {.forwards = false});
}

/*
 * @todo Flesh out this method before the competition in order to make it a full
 * solo awp autonomous. Blue right
 */
void Autonomous::BlueNeg(Intake &intake, Latch &latch, DistanceSensor &distance, LadyBrown &ladybrown) {

   
   // Blue Negative 4+1 & touch
   HookMotor.set_zero_position(HookMotor.get_position());
   colorSensor.set_led_pwm(70);
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   //Edge of lady brown is 5.5 inches from the alliance wall stake.
   chassis.setPose(0, 0, -112);
 
   ladybrown.MoveToPoint(LadyBrown::ATTACK_STATE, 150, 900);

   chassis.moveToPose(11, 44, 180, 2000, {.forwards=false, .horizontalDrift=5.5});

   ladybrown.MoveToPoint(LadyBrown::BASE_STATE, 150, 1000);
   chassis.waitUntilDone();
   LatchControl.extend();
   pros::delay(250);
   chassis.swingToPoint(28, 54.5, lemlib::DriveSide::LEFT, 1500, {.direction=AngularDirection::CCW_COUNTERCLOCKWISE});

   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(200);
   chassis.moveToPoint(28, 54.5, 5000);
   chassis.turnToPoint(43, 55, 5000);

   chassis.moveToPoint(43, 55, 2500, {.minSpeed = 65}, false);
   pros::delay(750);

   chassis.turnToPoint(19, 40, 1000, {.forwards=false});
   chassis.moveToPoint(19, 40, 1000, {.forwards=false});
   chassis.turnToPoint(38, 39, 1000);
   chassis.moveToPoint(38, 39, 1000);

   chassis.turnToPoint(-8, 16.5, 1000, {.direction=AngularDirection::CCW_COUNTERCLOCKWISE});
   chassis.moveToPoint(-8, 16.5, 7500, {.minSpeed=25, .earlyExitRange=10});
   chassis.waitUntil(10);
   IntakeLift.extend();

   chassis.moveToPoint(-8, 16.5, 7500, {.maxSpeed=20}, false);
   
   //IntakeMotor.brake();


}

void BlueNegBAK(Intake &intake, Latch &latch, DistanceSensor &distance, LadyBrown &ladybrown) {

   
   // Blue Negative 3+1 & touch
   HookMotor.set_zero_position(HookMotor.get_position());
   colorSensor.set_led_pwm(70);
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   //Edge of lady brown is 5.5 inches from the alliance wall stake.
   chassis.setPose(0, 0, -112);
 
   ladybrown.MoveToPoint(LadyBrown::ATTACK_STATE, 150, 900);

   chassis.moveToPose(11, 44, 180, 2000, {.forwards=false, .horizontalDrift=5.5});

   ladybrown.MoveToPoint(LadyBrown::BASE_STATE, 150, 1000);
   chassis.waitUntilDone();
   LatchControl.extend();
   pros::delay(250);
   chassis.swingToPoint(26, 55, lemlib::DriveSide::LEFT, 1500, {.direction=AngularDirection::CCW_COUNTERCLOCKWISE});

   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(200);
   chassis.moveToPoint(26, 55, 5000);
   chassis.turnToPoint(42, 55.5, 5000);

   chassis.moveToPoint(42, 55.5, 2500, {.minSpeed = 65}, false);
   pros::delay(750);

   chassis.turnToPoint(32, 40, 1000, {.forwards=false});
   chassis.moveToPoint(32, 40, 1000, {.forwards=false});
   chassis.turnToPoint(38, 39, 1000);
   chassis.moveToPoint(38, 39, 1000);

   chassis.turnToPoint(-5, 39, 1000, {.direction=AngularDirection::CCW_COUNTERCLOCKWISE});
   chassis.moveToPoint(-5, 39, 7500, {.minSpeed=25, .earlyExitRange=15});
   chassis.waitUntil(18);
   IntakeMotor.brake();

   
   //IntakeMotor.brake();

}

// Takes in two parameters: The autonomous value as well as the puncher object.
void Autonomous::AutoDrive(Intake &intake, Latch &latch, Sweeper &sweeper, DistanceSensor &distance,
                           LadyBrown &ladybrown) {
   // Keep the switcher running while the controller down button has not been pressed and the time period is not
   // autonomous Compare the current auton value to run the auton routine
   switch (Autonomous::auton) {
   case RED_NEG:
      Autonomous::autonName = "Red Negative";
      RedNeg(intake, latch, distance, ladybrown);
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
      BlueNeg(intake, latch, distance, ladybrown);
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