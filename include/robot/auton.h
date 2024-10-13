#pragma once
#include <string>

#include "robot/intake.h"
#include "robot/latch.h"

namespace Robot {
/**
 * @details We use Lemlib extensively for our documentation. You can find the documentation for Lemlib at
 * <A HREF="https://lemlib.github.io/lemlib/">Lemlib documentation</A>.
 * @brief The \ref Autonomous class contains classes and functions related to the robot's autonomous behavior.
 */
class Autonomous {
 public:
   enum AUTON_ROUTINE { RED_LEFT = 1, RED_RIGHT = 2, BLUE_LEFT = -1, BLUE_RIGHT = -2, SKILLS = 0 };

   /**
    * @brief Sets the number of the autonomous program to use.
    *
    * This function allows the user to specify the autonomous program to be executed by the robot.
    * The autonomous program number determines the specific actions and movements the robot will perform.
    *
    * @param auton The number of the autonomous program to use.
    */
   static AUTON_ROUTINE auton;

   /**
    * @brief The name of the autonomous program.
    * @details This variable stores the name of the autonomous program currently
    * selected. It is handled by the switching functions and the screen.
    */
   static std::string autonName;

   /**
    * @brief Drives the robot autonomously.
    *
    * This function drives the robot autonomously based on the selected
    * autonomous program. It takes a reference to a Puncher object and a boolean
    * value indicating whether to use autonomous mode.
    *
    * @param puncher A reference to the Puncher object.
    * @param autono A boolean value indicating whether to use autonomous mode.
    */
   void AutoDrive(Intake &intake, Latch &latch);

   /**
    * @brief Switches the autonomous program.
    *
    *
    * This function switches the autonomous program to the next available
    * program. It allows the user to cycle through different autonomous programs
    * during runtime.
    */
   static void AutonSwitcher(int autonNum);

 private:
   /**
    * @brief Runs the autonomous path for the far side defensive game strategy.
    *
    * This function executes the autonomous path for the far side defensive game
    * strategy. It contains the specific actions and movements required for this
    * strategy.
    */
   void Auton1(Intake &intake, Latch &latch);

   /**
    * @brief Runs the autonomous path for the near side offensive game strategy.
    *
    * This function executes the autonomous path for the near side offensive game
    * strategy. It contains the specific actions and movements required for this
    * strategy.
    */
   void Auton2(Intake &intake, Latch &latch);

   /**
    * @brief Runs the puncher routine for the Skills Challenge.
    *
    * This function executes the puncher routine for the Skills Challenge.
    * It takes a reference to a Puncher object and performs the necessary actions
    * for the challenge.
    *
    * @param puncher A reference to the Puncher object.
    */
   void Auton3(Intake &intake, Latch &latch);

   /**
    * @brief Runs the autonomous path for the far side offensive game strategy.
    * This function executes the autonomous path for the far side offensive game
    * strategy. It contains the specific actions and movements required for this
    * strategy.
    * @todo Make the autonomous more fleshed out, building it properly for the
    * competition
    */
   void Auton4(Intake &intake, Latch &latch);

   /**
    * Executes the Skills challenge autonomous.
    *
    * This function controls the robot's actions during autonomous routine 5.
    * It takes references to the `Intake` and `Latch` objects as parameters.
    *
    * @param intake The reference to the `Intake` object.
    * @param latch The reference to the `Latch` object.
    */
   void Auton5(Intake &intake, Latch &latch);
};
} // namespace Robot
