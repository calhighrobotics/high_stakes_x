#pragma once
#include "pros/apix.h"

namespace Robot {

    /**
     * @brief The selector screen allows for choosing modes that the drivetrain and autonomous take.
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
             * This function creates a tab view object and adds two tabs to it: "Autonomous select" and "Drive select".
             * It also adds event callbacks to the tabs for updating the UI.
             * The function creates labels, switches, and a dropdown list for selecting alliance
             * color, skills, and autonomous mode.
             * It also creates a label and a roller for selecting the current drive mode.
             */
            void selector();

        private:

            /**
             * @brief Value of the last selected competition autonomous when switching to a skills autonomous.
             */
            static int lastAuton;

            static void auton_ui_update(lv_event_t * e);
           
            /** The 2 event handlers and 1 helper function for the autonomous routine 
            * cannot be put here, as they are static in a different connotation than
            * their header counterparts. They are instead put in the source file
            * (screen/selector.cpp).
            */     
    };
}