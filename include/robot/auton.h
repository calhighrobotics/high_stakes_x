#pragma once


namespace Robot {
    /// @brief Sets the number of the autonomuos program to use.

    class Autonomous {
    
    public:
        static int auton;
        extern bool AutonSwitch;
    
    void AutoDrive();
    void AutonSwitcher();

    };
}