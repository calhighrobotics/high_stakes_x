// Header guard - Ensures that the header file will not get double imported.
#pragma once

namespace Robot {

    class Drivetrain {
    // int deadzone needs to be external in order to allow other files to see and modify the variable. Otherwise, will be redefined and made unavailable for usage.

    public:
        /// @brief Run the drivetrain depending on the control mode.
        void run();
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
        /// @brief Switches the DriveTrain mode.
        void SwitchDrive();
        /// @brief Contains the current drive train mode.
        int driveMode;
        /// @brief initiates field values
        Drivetrain();
    private:
        /// @brief left joystick(forward,backward); right joystick(left, right)
        void ArcadeDrive();
        /// @brief left and right joystick
        void TankDrive();
        /**
            @brief Verifies that the controller input is inside the deadzone range.
            @param int entry controller input
        */
        int CheckDeadzone(int entry);
        /// deadzone value
        int deadzone;

    };
}