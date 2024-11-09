#include "electronic/controller.h"
#include "globals.h"
#include "pros/misc.h"

using namespace Robot;
using namespace Robot::Globals;

void Controller::notifier() {

   // No direct translation to morse code.
   if (partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
      controller.rumble("..-");
   }
   // Stands for "R" in morse code.
   if (partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
      controller.rumble(".-.");
   }
   // No direct translation to morse code.
   if (partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
      controller.rumble("-..");
   }
   // Stands for "K" in morse code.
   if (partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
      controller.rumble("-.-");
   }

   // Special rumble in order to notify of only 15 seconds remaining.
   if (partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
      controller.rumble("...");
   }
}

void Controller::switchControl() {
   // Dynamic controller switching - Switches which controller is main between the dual controllers
   if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2) && partner.is_connected()) {
      pros::Controller temp = controller;

      controller = partner;
      partner = temp;

      controller.print(0, 0, "Main Controller");

      pros::delay(50);

      partner.print(0, 0, "Partner Controller");
   }
}

Controller::Controller() { ; }