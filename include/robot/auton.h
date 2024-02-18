#pragma once


#include "drivetrain.h"
#include "puncher.h"

namespace Robot {
    /// @brief Sets the number of the autonomuos program to use.

    class Autonomous {
    
    public:
        // Doxygen comments
        /// @brief Sets the number of the autonomuos program to use.
        static int auton;

        /// @brief Main function .
        void AutoDrive(Puncher &puncher, bool autono);
        void AutonSwitcher();

    private:
        void Auton1();
        void Auton2();
        void Auton3(Puncher &puncher);

    };
}