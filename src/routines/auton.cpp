#include "robot/auton.h"
#include "main.h" // IWYU pragma: export

using namespace Robot;
using namespace Robot::Globals;

Autonomous::AUTON_ROUTINE Autonomous::auton = RED_LEFT;
std::string Autonomous::autonName;

// Red Left
void Autonomous::Auton1(Intake &intake, Latch &latch) {}

// Red Right
void Autonomous::Auton2(Intake &intake, Latch &latch) {}

// Blue left
void Autonomous::Auton3(Intake &intake, Latch &latch) {}

/*
 * @todo Flesh out this method before the competition in order to make it a full
 * solo awp autonomous. Blue right
 */
void Autonomous::Auton4(Intake &intake, Latch &latch) {}

void Autonomous::Auton5(Intake &intake, Latch &latch) {
   // Autonomous routine for the Skills challenge
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