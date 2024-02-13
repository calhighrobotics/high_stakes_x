#pragma once


#include "drivetrain.h"
namespace Robot {
    /// @brief Sets the number of the autonomuos program to use.

    class Autonomous {
    
    public:
        // Doxygen comments
        /// @brief Sets the number of the autonomuos program to use.
        static int auton;

        /// @brief Main function .
        void AutoDrive(bool autono);
        void AutonSwitcher();

    private:
        void Auton1();
        void Auton2();
        void Auton3();

    };
}