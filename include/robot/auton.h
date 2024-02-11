#pragma once


#include "drivetrain.h"
namespace Robot {
    /// @brief Sets the number of the autonomuos program to use.

    class Autonomous {
    
    public:
        static int auton;
        void AutoDrive();
        void AutonSwitcher();

    private:
        void Auton1();
        void Auton2();
        void Auton3();

    };
}