#pragma once

namespace Robot {

    /**
     * @brief The Intake class represents a robot intake system.
     */
    class Intake {
    public:
        /**
         * @brief Runs the main function of the intake system.
         * 
         * Takes user input to control the direction of the intake system.
         */
        void run(unsigned short direction);

        /**
         * @brief Outakes rings and scores them inside of latched mobile goal.
         */
        void score();

        /**
         * @brief Controls the latching mechanism of the latch class.
         */
        void latch();
    };
}