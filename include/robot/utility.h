#pragma once


#include "auton.h"
#include "drivetrain.h"
#include "puncher.h"

namespace Robot {
    
    namespace Utility {
        void displayLocation();
        void displayMotorVel();
        void toggleSubsystemOptions(Autonomous &auton, Drivetrain &drive, Puncher &punch);
    }
}
