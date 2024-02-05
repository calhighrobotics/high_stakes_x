#pragma once


namespace Autonomous {
    /// @brief Sets the number of the autonomuos program to use.
    extern int auton;
    extern bool AutonSwitch;
    
    void AutoDrive();
    void AutonSwitcher();
}