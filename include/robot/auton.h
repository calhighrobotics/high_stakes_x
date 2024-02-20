#pragma once

#include "puncher.h"

namespace Robot {
    /// @brief Sets the number of the autonomuos program to use.

    class Autonomous {
    
    public:
        // Doxygen comments
        /// @brief Sets the number of the autonomuos program to use.
        static int auton;

        /**
	        @brief Auton Selector.  Selects the auton path to run.
	        @param Puncher puncher Puncher object.
	        @param bool autono Represents if the down button is pressed to toggle selector.
        */
        void AutoDrive(Puncher &puncher, bool autono);
        
        /// @brief Switches the autonomous program.
        void AutonSwitcher();

    private:
	    /// @brief Runs the Auton path for the far side defensive game stategy.
        void Auton1();
	    /// @brief Runs the Auton path for near side offensive game strategy.
        void Auton2();
        /**
	        @brief Runs the puncher routine for the Skills Challenge.
	        @param Puncher puncher Puncher object.
        */
        void Auton3(Puncher &puncher);

    };
}