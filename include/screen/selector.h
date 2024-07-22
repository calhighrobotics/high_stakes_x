#pragma once

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
             * @brief Main function that is called by the entrypoint.
             */
            void selector();

        private:

            
            /**
             * @brief Updates the autonomous selector screen.
             *
             * This function is responsible for updating the autonomous selector screen based on the
             * given event.
             *
             * @param e The event that triggered the update.
             */
            static void auton_update(lv_event_t * e);

            /**
             * @brief Updates the drive selector screen.
             *
             * This function is responsible for updating the drive selector screen based on the
             * given event.
             *
             * @param e The event that triggered the update.
             */
            static void drive_update(lv_event_t * e);

    };
}