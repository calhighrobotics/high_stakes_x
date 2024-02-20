
// Header guard - Ensures that the header file will not get double imported.
#pragma once

namespace Robot {

    class Drivetrain {
    // int deadzone needs to be external in order to allow other files to see and modify the variable. Otherwise, will be redefined and made unavailable for usage.

    public:
        void run();
        /// @brief left joystick(forward,backward); right joystick(left, right)
        void ArcadeDrive();
        /// @brief left and right joystick
        void TankDrive();
        /**
            @brief Sets joystick deadzone
            @param int newDeadZone new deadzone value
        */
        void setdeadzone(int newDeadZone);
        /**
            @brief returns the current deadzone value
            @return dead zone value
        */
        int getdeadzone();
        void SwitchDrive();
        int driveMode;
        Drivetrain();
    private:
        /**
            @brief Verifies that the controller input is inside the deadzone range.
            @param int entry controller input
        */
        int CheckDeadzone(int entry);
        int deadzone;

    };
}