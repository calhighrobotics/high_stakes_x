#include "main.h"
#include "globals.h"
#include "pros/misc.h"
#include "robot/drivetrain.h"
#include "screen/selector.h"
#include "screen/status.h"

using namespace Robot;
using namespace Robot::Globals;
/*
 ____ .____________  ____________  ___
/_   ||   ____/_   |/  _____/\   \/  /
 |   ||____  \ |   /   __  \  \     /
 |   |/       \|   \  |__\  \ /     \
 |___/______  /|___|\_____  //___/\  \
            \/            \/       \_/

*/

/**
 * @file main.cpp
 * @brief This file contains the main code for the robot's operation.
 */

/**
 * @brief Structure that holds instances of all robot subsystems.
 */
struct RobotSubsystems {
   Robot::Autonomous autonomous;
   Robot::Drivetrain drivetrain;
   Robot::Intake intake;
   Robot::Latch latch;
   Robot::Hang hang;
} subsystem;

struct RobotScreen {
   Robot::selector_screen selector;
   Robot::status_screen status;
} screen;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
   chassis.calibrate();

   chassis.setPose(0, 0, 0);

   // screen.selector.selector();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */

void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.<asd></asd>
 */
void competition_initialize() {}

/**6
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start
 * it from where it left off.
 */

void autonomous() {

   pros::lcd::initialize();
   pros::Task screen_task([&]() {
      while (true) {
         // print robot location to the brain screen
         pros::lcd::print(0, "X: %f", chassis.getPose().x);         // x
         pros::lcd::print(1, "Y: %f", chassis.getPose().y);         // y
         pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
         // delay to save resources
         pros::lcd::print(3, "Rotation Sensor: %i", lateral_sensor.get_position());
         pros::lcd::print(4, "Rotation Sensor: %i", horizontal_sensor.get_position());
         pros::delay(20);
      }
   });

   subsystem.autonomous.AutoDrive(subsystem.intake, subsystem.latch);
}

/**
 * Runs the operator control code. This function will be started in its own
 * task with the default priority and stack size whenever the robot is enabled
 * via the Field Management System or the VEX Competition Switch in the
 * operator control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart
 * the task, not resume it from where it left off.
 */
void opcontrol() {
   while (true) {
      if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
         autonomous();
      }
      if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
         std::string name = subsystem.drivetrain.toggleDrive();
         // Output the current drive mode to the controller screen
         controller.print(0, 0, name.c_str());
      }
      if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
         Drivetrain::isReversed = !Drivetrain::isReversed;
         // Output the current drive mode to the controller screen

         controller.print(0, 0, "reversal: %d", Drivetrain::isReversed);
      }

      subsystem.drivetrain.run();
      subsystem.latch.run();
      subsystem.hang.run();

      // Intake controller, uses the X button holded down to push the elevation
      // up.
      subsystem.intake.run();

      // Intake controller, moves the left and right intakes and stops them if
      // nothing is pressed.

      pros::delay(10); // Small delay to reduce CPU usage
   }
}