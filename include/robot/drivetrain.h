
// Header guard - Ensures that the header file will not get double imported.
#pragma once

namespace Drivetrain {
    // int deadzone needs to be external in order to allow other files to see and modify the variable. Otherwise, will be redefined and made unavailable for usage.
    extern int deadzone;
    void ArcadeDrive();
    void TankDrive();
};