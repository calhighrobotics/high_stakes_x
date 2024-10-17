#pragma once
#include "pros/apix.h" // IWYU pragma: export
#include "robot/auton.h"

namespace Robot {

/**
 * @brief The selector screen allows for choosing modes that the drivetrain and
 * autonomous take.
 */
class selector_screen {
 public:
   /**
    * @brief Constructor.
    */

   selector_screen();

   /**
    * @brief Function to create and initialize the selector screen.
    *
    * This function creates a tab view object and adds two tabs to it:
    * "Autonomous select" and "Drive select". It also adds event callbacks to the
    * tabs for updating the UI. The function creates labels, switches, and a
    * dropdown list for selecting alliance color, skills, and autonomous mode. It
    * also creates a label and a roller for selecting the current drive mode.
    */
   void selector();

 private:
   /**
    * @brief Value of the last selected competition autonomous when switching to
    * a skills autonomous.
    */
   static Autonomous::AUTON_ROUTINE lastAuton;

   /**
    * @brief Red alliance autonomous routines
    * @see AUTON_ROUTINE
    *
    * Must be new line seperated to pass to LVGL. Each one should match its
    * corresponding autonomous routine defined in auton.h
    */
   constexpr static char redAutons[] = "Red Left\nRed Right";

   /**
    * @brief Blue alliance autonomous routines
    * @see AUTON_ROUTINE
    *
    * Must be new line seperated to pass to LVGL. Each one should match its
    * corresponding autonomous routine defined in auton.h
    */
   constexpr static char blueAutons[] = "Blue Left\nBlue Right";

   /**
    * @brief Drive control schemes
    * @see DRIVE_MODE
    *
    * Must be new line seperated to pass to LVGL. Each drive mode should match
    * its corresponding drive mode defined in drivetrain.h
    */
   constexpr static char driveModes[] = "Curvature Drive\nArcade Drive\nTank Drive";

   /**
    * @brief LVGL callback to update the autonomous when widget values are
    * updated.
    * @param e Pointer to a LVGL event.
    *
    * All interactable widgets on the autonomous tab bubble their events to
    * this function. It checks which widget was updated and applies the
    * corresponding logic for updating the autonomous routine.
    */
   static void auton_ui_update(lv_event_t *e);

   /**
    * @brief LVGL callback to update the drive mode when widget values are
    * updated.
    * @param e Pointer to a LVGL event.
    *
    * The roller widget on the drive mode tab bubbles their events to this
    * function. It updates the driving control scheme of the robot with the
    * index of the roller widget.
    */
   static void drive_update(lv_event_t *e);
};
} // namespace Robot