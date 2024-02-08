
// Header guard - Ensures that the header file will not get double imported.
#pragma once

namespace Robot {

    class Drivetrain {
    // int deadzone needs to be external in order to allow other files to see and modify the variable. Otherwise, will be redefined and made unavailable for usage.

    public:
        void ArcadeDrive();
        void TankDrive();
        void setdeadzone(int newDeadZone);
        int getdeadzone();
    private:
        int CheckDeadzone();
        int deadzone;

    };
}