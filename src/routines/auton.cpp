#include "robot/auton.h"
#include "globals.h"
#include "main.h" // IWYU pragma: export
#include "pros/motors.h"
#include "pros/rtos.hpp"


using namespace Robot;
using namespace Robot::Globals;

Autonomous::AUTON_ROUTINE Autonomous::auton = RED_LEFT;
std::string Autonomous::autonName;
uint32_t delay_constant = 1050;

ASSET(red_right_pt1_txt);
ASSET(red_right_pt2_txt);
ASSET(red_right_pt3_txt);
ASSET(red_right_pt4_txt);
ASSET(red_right_pt5_txt);

ASSET(red_left_pt1_txt);
ASSET(red_left_pt2_txt);
ASSET(red_left_pt3_txt);
ASSET(red_left_pt4_txt);
ASSET(red_left_pt5_txt);

// Red Left
void Autonomous::Auton1(Intake &intake, Latch &latch) {
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   pros::delay(950);
   chassis.setPose(0, 0,0);
   IntakeMotor.move_relative(-900, 100);
   chassis.moveToPoint(0, 29, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);
   latch.toggle();
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   // get bottom red ring north
   chassis.turnToHeading(-45, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.setPose(0,0,0);
   chassis.moveToPoint(0, 29, 1400, {.forwards = false, .maxSpeed = 70}, true);
   pros::delay(delay_constant);
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   latch.toggle();
   chassis.turnToHeading(90, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.setPose(0,0,0);
   chassis.moveToPoint(0, -29, 1400, {.forwards = false, .maxSpeed = 70}, true);
   pros::delay(delay_constant);
}

// Red Right
void Autonomous::Auton2(Intake &intake, Latch &latch) {
   //HangControl.toggle();
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   pros::delay(950);
   chassis.setPose(0, 0,0);
   IntakeMotor.move_relative(-900, 100);
   chassis.moveToPoint(0, -29, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);
   latch.toggle();
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   //going for the south bottom red ring
   chassis.turnToHeading(45, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.setPose(0,0,0);
   chassis.moveToPoint(0, -60, 1400, {.forwards = false, .maxSpeed = 70}, true);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);

   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   //going for the third ring, north, on middle line of red side
   chassis.turnToHeading(22, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.setPose(0,0,0);
   chassis.moveToPoint(-60, 120, 1400, {.forwards=false, .maxSpeed = 70}, true);
   pros::delay(delay_constant);
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   // touching tower
   latch.toggle();
   chassis.turnToHeading(78, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.setPose(0,0,0);
   chassis.moveToPoint(-30, 0, 1400, {.forwards=false, .maxSpeed = 70}, true);
   pros::delay(delay_constant);


   //chassis.moveToPoint(0, 4, 1000, {.forwards = true, .maxSpeed = 95}, true);
}

// Blue left
void Autonomous::Auton3(Intake &intake, Latch &latch) {
   //HangControl.toggle();
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   pros::delay(950);
   chassis.setPose(0, 0,0);
   IntakeMotor.move_relative(-900, 100);
   chassis.moveToPoint(0, 29, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);
   latch.toggle();
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   //going for the south both red ring
   chassis.turnToHeading(-45, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.setPose(0,0,0);
   chassis.moveToPoint(0, 60, 1400, {.forwards = false, .maxSpeed = 70}, true);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);

   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   //going for the third ring, north, on middle line of red side
   chassis.turnToHeading(-22, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.setPose(0,0,0);
   chassis.moveToPoint(60, -120, 1400, {.forwards=false, .maxSpeed = 70}, true);
   pros::delay(delay_constant);
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   // touching tower
   latch.toggle();
   chassis.turnToHeading(-78, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.setPose(0,0,0);
   chassis.moveToPoint(30, 0, 1400, {.forwards=false, .maxSpeed = 70}, true);
   pros::delay(delay_constant);




   /*HangControl.toggle();
   pros::delay(950);
   HangControl.toggle();*/
}

/*
 * @todo Flesh out this method before the competition in order to make it a full
 * solo awp autonomous. Blue right
 */
void Autonomous::Auton4(Intake &intake, Latch &latch) {
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   pros::delay(950);
   chassis.setPose(0, 0,0);
   IntakeMotor.move_relative(-900, 100);
   chassis.moveToPoint(0, -29, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);
   latch.toggle();
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   // get bottom red ring north
   chassis.turnToHeading(45, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.setPose(0,0,0);
   chassis.moveToPoint(0, -29, 1400, {.forwards = false, .maxSpeed = 70}, true);
   pros::delay(delay_constant);
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   latch.toggle();
   chassis.turnToHeading(-90, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.setPose(0,0,0);
   chassis.moveToPoint(0, 29, 1400, {.forwards = false, .maxSpeed = 70}, true);
   pros::delay(delay_constant);
}


// SKILLS
void Autonomous::Auton5(Intake &intake, Latch &latch) {
   drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   pros::delay(950);
   chassis.setPose(0, 0,0);
   IntakeMotor.move_relative(-900, 100);

   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   chassis.moveToPoint(0, 53, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);
   chassis.turnToHeading(90, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);

   chassis.setPose(0,0,0);
   chassis.moveToPoint(0, -45, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);

   latch.toggle();
   chassis.turnToHeading(-90, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.moveToPoint(53, 0, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);
   
   //intake first ring
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   chassis.setPose(0,0,0);
   chassis.turnToHeading(-68, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.moveToPoint(60, -90, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);

   //intake second ring
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   chassis.setPose(0,0,0);
   chassis.turnToHeading(-135, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.moveToPoint(-56, 30, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);

   //intake third ring
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   chassis.setPose(0,0,0);
   chassis.turnToHeading(23, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.moveToPoint(-60, -30, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);

   //intake fourth ring
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   chassis.setPose(0,0,0);
   chassis.moveToPoint(0, 30, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);

   //intake fifth ring
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   chassis.setPose(0,0,0);
   chassis.turnToHeading(113, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.moveToPoint(32, -28, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);

   //intake sixth ring
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   chassis.setPose(0,0,0);
   chassis.turnToHeading(90, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.moveToPoint(-60, 0, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);

   //release mobile goal
   latch.toggle();

   chassis.setPose(0,0,0);
   chassis.moveToPoint(0, 60, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);
   chassis.turnToHeading(-157, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);




   //other side


   chassis.setPose(0,0,0);
   chassis.moveToPoint(0, -150, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);

   //other side



   chassis.setPose(0,0,0);
   chassis.moveToPoint(0, -45, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);

   latch.toggle();
   chassis.turnToHeading(-90, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.moveToPoint(53, 0, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);
   
   //intake first ring
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   chassis.setPose(0,0,0);
   chassis.turnToHeading(-68, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.moveToPoint(60, -90, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);

   //intake second ring
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   chassis.setPose(0,0,0);
   chassis.turnToHeading(-135, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.moveToPoint(-56, 30, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);

   //intake third ring
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   chassis.setPose(0,0,0);
   chassis.turnToHeading(23, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.moveToPoint(-60, -30, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);

   //intake fourth ring
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   chassis.setPose(0,0,0);
   chassis.moveToPoint(0, 30, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);

   //intake fifth ring
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   chassis.setPose(0,0,0);
   chassis.turnToHeading(113, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.moveToPoint(32, -28, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);

   //intake sixth ring
   IntakeMotor.move_velocity(-600);
   HookMotor.move_velocity(-350);
   pros::delay(delay_constant * 2);
   IntakeMotor.move_velocity(0);
   HookMotor.move_velocity(0);

   chassis.setPose(0,0,0);
   chassis.turnToHeading(90, 1400, {.maxSpeed = 70}, true);
   pros::delay(delay_constant);
   chassis.moveToPoint(-60, 0, 1400, {.forwards = false, .maxSpeed = 70},true);
   pros::delay(delay_constant);

   //release mobile goal
   latch.toggle();




}

// Takes in two parameters: The autonomous value as well as the puncher object.
void Autonomous::AutoDrive(Intake &intake, Latch &latch) {
   // Keep the switcher running while the controller down button has not been pressed and the time period is not
   // autonomous Compare the current auton value to run the auton routine
   switch (Autonomous::auton) {
   case RED_LEFT:
      Auton1(intake, latch);
      break;
   case RED_RIGHT:
      Auton2(intake, latch);
      break;
   case BLUE_LEFT:
      Auton3(intake, latch);
      break;
   case BLUE_RIGHT:
      Auton4(intake, latch);
      break;
   case SKILLS:
      Auton5(intake, latch);
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