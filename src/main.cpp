#include "main.h"
#include "electronic/controller.h"
#include "electronic/distance.h"
#include "globals.h"
#include "lemlib/chassis/chassis.hpp"
#include "liblvgl/llemu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
#include "robot/auton.h"
#include "robot/drivetrain.h"
#include "robot/ladybrown.h"
#include "robot/lift.h"
#include "screen/selector.h"
#include "screen/status.h"
#include <string>
#include <cmath>

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
   Robot::Lift lift;
   Robot::Latch latch;
   Robot::LadyBrown ladybrown;
   Robot::Sweeper sweeper;
} subsystem;

struct RobotScreen {
   Robot::selector_screen selector;
   Robot::status_screen status;
} screen;

struct Electronics {
   Robot::Controller controllers;
   Robot::DistanceSensor distance_sensor;
} electronic;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
   chassis.calibrate();

   //Also used for ringskip

   chassis.setPose(0, 0, 0);
   pros::rtos::Task MotorNotification(electronic.controllers.notify_motor_disconnect);

   Autonomous::auton = Autonomous::RED_NEG;

   pros::lcd::initialize();
   pros::Task screen_task([&]() {
      while (true) {
         // print robot location to the brain screen
         pros::lcd::print(0, "X: %f", chassis.getPose().x);         // x
         pros::lcd::print(1, "Y: %f", chassis.getPose().y);         // y
         pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
         // delay to save resources
         pros::lcd::print(3, "Lateral Sensor: %i", lateral_sensor.get_position());
         pros::lcd::print(4, "Horizontal Sensor: %i", horizontal_sensor.get_position());
         pros::lcd::print(5, "Lady Brown Sensor: %i", LadyBrownRotation.get_position());
         pros::lcd::print(6, "Autonomous: %s", subsystem.autonomous.autonName);

         //std::cout << "Hook Pos  =  " << HookRotation.get_position() % 83540 << std::endl;


         pros::delay(190);
      }
   });

   //@TODO: Put the following into a seperate class.
   // pros::Task screen_task([&]() {
   //    lv_obj_t *chart = lv_chart_create(lv_scr_act());
   //    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
   //    lv_chart_set_point_count(chart, 460);
   //    lv_obj_set_size(chart, 460, 220);
   //    lv_obj_center(chart);
   //    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, -15250, -14750);
   //    lv_chart_set_zoom_y(chart, 600);
   //    lv_chart_set_zoom_x(chart, 1000);
   //    lv_obj_set_style_size(chart, 0, LV_PART_INDICATOR);
   //    lv_chart_series_t *s1 = lv_chart_add_series(chart, lv_color_white(), LV_CHART_AXIS_PRIMARY_Y);
   //    lv_chart_series_t *s2 = lv_chart_add_series(chart, lv_color_hex(0xFFFF0000), LV_CHART_AXIS_SECONDARY_X);

   //    lv_obj_t * label = lv_label_create(lv_scr_act());
   //    lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0xffffff), LV_PART_MAIN);
   //    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);
   //    lv_obj_set_style_text_font(label, &lv_font_montserrat_20, 0);

   //    while (true) {
   //       lv_chart_set_next_value(chart, s1, subsystem.ladybrown.get_target());
   //       lv_chart_set_next_value(chart, s2, LadyBrownRotation.get_position());
   //       if (pros::millis() >= 5000) {
   //          std::string angle = std::to_string(LadyBrownRotation.get_position());
   //          lv_label_set_text(label, angle.c_str());
   //          break;
   //       }
   //       pros::delay(10);
   //    }
   // });

   pros::rtos::Task Task(electronic.controllers.notify_motor_disconnect);
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
void competition_initialize() {
   screen.selector.selector();

}

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
      pros::Task screen_task([&]() {
      pros::lcd::initialize();
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
   
   subsystem.autonomous.AutoDrive(subsystem.lift, subsystem.latch, subsystem.sweeper, electronic.distance_sensor,
                                  subsystem.ladybrown);
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

      // Calls to event handling functions.
      if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
         autonomous();
      }
      // Toggles the drivetrain orientation - can be forward or backward
      if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
         std::string name = subsystem.drivetrain.toggleDrive();
         // Output the current drive mode to the controller screen
         controller.print(0, 0, name.c_str());
      }
      // Checks for drivetrain reversal - Changes conditions in a value handler function in the drivetrain class
      if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
         // isReversed is static, it is changed for the global state.
         Lift::ringSkipActive = !Lift::ringSkipActive;

         // Output the current drive mode to the controller screen
         controller.print(0, 0, "riskip: %d", Lift::ringSkipActive);
      }

      if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
         pros::Task move([&]() { subsystem.ladybrown.MoveToPoint(LadyBrown::ATTACK_STATE); }, "LadyBrownMove");
      }


      subsystem.drivetrain.run();
      subsystem.latch.run();
      subsystem.sweeper.run();
      subsystem.ladybrown.run();

      // Intake controller - uses R1 to pull in and L1 to push out, and stops if nothing pressed
      subsystem.lift.run();

      // Handles partner controller keypresses to rumble the primary controller
      electronic.controllers.notifier();

      // DOES NOT SWITCH CONTROL - Checks for a key press to trigger controller switch
      electronic.controllers.switchControl();

      pros::delay(10); // Small delay to reduce CPU usage
   }
}
