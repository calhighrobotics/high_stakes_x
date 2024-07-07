#pragma once
#include <string>

namespace Robot {
    /**
     * @details We use Lemlib extensively for our documentation. You can find the documentation for Lemlib at
     * <A HREF="https://lemlib.github.io/lemlib/">Lemlib documentation</A>.
     * @brief The \ref Autonomous class contains classes and functions related to the robot's autonomous behavior.
     */
    class Autonomous {
    
    public:
        /**
         * @brief Sets the number of the autonomous program to use.
         * 
         * This function allows the user to specify the autonomous program to be executed by the robot.
         * The autonomous program number determines the specific actions and movements the robot will perform.
         * 
         * @param auton The number of the autonomous program to use.
         */
        static int auton;

        /**
         * @brief Drives the robot autonomously.
         * 
         * This function drives the robot autonomously based on the selected autonomous program.
         * It takes a reference to a Puncher object and a boolean value indicating whether to use autonomous mode.
         * 
         * @param puncher A reference to the Puncher object.
         * @param autono A boolean value indicating whether to use autonomous mode.
         */
        void AutoDrive(bool autono);
        
        /**
         * @brief Switches the autonomous program.
         * 
         * @details Make sure to pass in a reference to the Puncher object with .
         * 
         * This function switches the autonomous program to the next available program.
         * It allows the user to cycle through different autonomous programs during runtime.
         */
        void AutonSwitcher();

    private:
        /**
         * @brief Runs the autonomous path for the far side defensive game strategy.
         * 
         * This function executes the autonomous path for the far side defensive game strategy.
         * It contains the specific actions and movements required for this strategy.
         */
        void Auton1();

        /**
         * @brief Runs the autonomous path for the near side offensive game strategy.
         * 
         * This function executes the autonomous path for the near side offensive game strategy.
         * It contains the specific actions and movements required for this strategy.
         */
        void Auton2();

        /**
         * @brief Runs the puncher routine for the Skills Challenge.
         * 
         * This function executes the puncher routine for the Skills Challenge.
         * It takes a reference to a Puncher object and performs the necessary actions for the challenge.
         * 
         * @param puncher A reference to the Puncher object.
         */
        void Auton3();

        void Auton4();

        std::string autonName;
    };
}
