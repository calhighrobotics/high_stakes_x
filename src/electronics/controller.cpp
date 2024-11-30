#include "electronic/controller.h"
#include "globals.h"
#include "pros/misc.h"
#include <cstdint>
#include <string>
#include <sys/_intsup.h>

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

void Controller::notify_motor_disconnect(void *param) {
   std::vector<pros::Motor> all_motors = pros::Motor::get_all_devices();
   std::vector<unsigned char> disconnected;
   std::vector<unsigned char> last_disconnected;
   bool is_notified = false;
   uint32_t now = pros::millis();

   const int TASK_DELAY_MILLIS = 1000;
   const int CONTROLLER_DELAY_MILLIS = 50;

   while (true) {
      std::string disc_motors = "MD: ";
      bool are_motors_disconnected = false;

      for (pros::Motor i : all_motors) {
         if (!i.is_installed()) {
            unsigned char port = i.get_port();
            disconnected.push_back(port);
            disc_motors = disc_motors + " " + std::to_string(port);
            are_motors_disconnected = true;
         }
      }
      // Controller screen commands must be delayed by 50ms due to polling limitations
      if (are_motors_disconnected) {
         controller.clear_line(0);
         pros::delay(CONTROLLER_DELAY_MILLIS);
         controller.set_text(0, 0, disc_motors);
         is_notified = true;
         pros::delay(CONTROLLER_DELAY_MILLIS);
      }
      if (disconnected.size() > last_disconnected.size()) {
         controller.rumble(". . .");
      } else if (disconnected.size() < last_disconnected.size()) {
         controller.rumble("-");
      } else if (!are_motors_disconnected && is_notified) {
         controller.clear_line(0);
         is_notified = false;
      }
      last_disconnected = disconnected;
      disconnected.clear();
      pros::Task::delay_until(&now, TASK_DELAY_MILLIS);
   }
}

Controller::Controller() { ; }