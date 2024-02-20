#pragma once


#include "auton.h"
#include "drivetrain.h"
#include "puncher.h"

namespace Robot {
    /**
     * @brief Contains utility functions for controlling the screen and toggling subsystems.
     */
    namespace Utility {
        /// @brief Displays current position of the robot.
        void displayLocation();
        /// @brief Displays current velocity of the robot.
        void displayMotorVel();
        /** 
            @brief Toggles subsystems, drive mode auton routine, and puncher.
            @param Autonomous auton Auton object.
            @param Drivetrain drive Drivetrain object.
            @param Puncher punch Puncher object.
        */
        void toggleSubsystemOptions(Autonomous &auton, Drivetrain &drive, Puncher &punch);
    }
}
