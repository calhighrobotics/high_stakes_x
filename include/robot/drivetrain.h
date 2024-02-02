#include "main.h"
// Header guard - Ensures that the header file will not get double imported.
#pragma once

class Drivetrain {
    public:
        static int deadzone;
        static void ArcadeDrive();
        static void TankDrive();
};