#include "electronic/distance.h"
#include "pros/motors.h"
#include "robot/auton.h"
#include "globals.h"
#include "lemlib/chassis/chassis.hpp"
#include "main.h" // IWYU pragma: export
#include "pros/rtos.hpp"
#include "robot/ladybrown.h"
#include "robot/sweeper.h"
#include <iostream>

using namespace Robot;
using namespace Robot::Globals;

// Skills
void Autonomous::Skills(Intake &intake, Latch &latch, DistanceSensor &distance, LadyBrown &ladybrown) {
   
   // Set pre-constants 
   HookMotor.set_zero_position(HookMotor.get_position());
   colorSensor.set_led_pwm(70);
   //drive_.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
   chassis.setPose(-5.25, 7.75, 180);

   //Autonomous routine for the Skills challenge - 60 seconds MAX
   /* ##############################################*/

   // De-hook into the alliance stake
   ladybrown.MoveToPoint(LadyBrown::ATTACK_STATE, 150, 750);

   // //Move to the center, then turn to and touch the right side Mogo.
   //chassis.moveToPoint(-5.25, 15, 800, {.forwards = false});

   //NOTE - MOGO INCONSISTENT BECAUSE OF INCORRECT ANGLE
   chassis.turnToPoint(24, 15.5, 1000, {.forwards = false});
   //chassis.moveToPoint(17.5, 15, 1850, {.forwards = false, .earlyExitRange=0.5}, false);
   chassis.moveToPoint(24, 15.5, 2000, {.forwards = false, .minSpeed=25, .earlyExitRange=18});
   chassis.moveToPoint(25, 15.5, 1000, {.forwards=false, .maxSpeed=30});
   chassis.waitUntilDone();

   // //Latch the mogo - delays just in case
   LatchControl.extend();
   pros::delay(250);

   // //Turn to the above ring - Start intake and hook, and move there
   chassis.turnToPoint(24, 38.75, 850, {}, true);
   ladybrown.MoveToPoint(LadyBrown::BASE_STATE);
   chassis.waitUntilDone();
   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(200);
   chassis.waitUntilDone();
   chassis.moveToPoint(24, 38.75, 1000);

   // Immediately move to the farthest ring. A couple of other things happen while this is going on
   chassis.moveToPose(48, 90, 0, 2050, {.horizontalDrift = 8, .lead = 0.45, .earlyExitRange=2}, true);
   //Checks between 10-45 inches of movement for if the hook got stuck on the mogo flower
   for (int i = 10; i<45; i += 5) {
   chassis.waitUntil(i);
   std::cout << "velocity" << HookMotor.get_actual_velocity() << std::endl;
   //Checks every 5 inches for if the hook gets stuck.
   while (HookMotor.get_actual_velocity() < 25 && !(colorSensor.get_hue() < 30 && colorSensor.get_hue() > 8)) {
      //FIX: The hook is lifted back and then hit into the target to ensure fit.
      HookMotor.move_velocity(-200);
      pros::delay(150);
      HookMotor.move_velocity(200);
      pros::delay(350);
   }
   //Lift up the Lady brown to load onto at 40 inches from the last position.
   }
   
   chassis.waitUntil(50);
   ladybrown.MoveToPoint(LadyBrown::LOAD_STATE);

   

   //Set the hook to a high-torque rpm to get the best loading possible, waits for the MoveToPose to end.
   HookMotor.move_velocity(200);
   chassis.waitUntilDone();
   //Turn to a point ~1.5 tiles away from the right neutral stake
   chassis.turnToPoint(41, 61.5, 800, {.forwards=false});

   //Actually move there
   chassis.moveToPoint(41, 61.5,1500, {.forwards=false}, true);

   chassis.waitUntilDone();

   //Turn to the Neutral wall stake.
   //chassis.turnToPoint(79, 63.5, 750);
   chassis.turnToPoint(72, 61.5,800);
   // Move there
   chassis.moveToPoint(68, 61.5,1500, {.forwards=true, .maxSpeed=75, .minSpeed=50, .earlyExitRange=6}, true);

   // At 18 inches of movement, stop the intake in advance of the neutral wall stake
   chassis.waitUntil(18);
   IntakeMotor.brake();
   HookMotor.brake();


   chassis.waitUntilDone();

   //Allow the robot to settle, then move the lady brown to score on the neutral stake.

   ladybrown.MoveToPoint(LadyBrown::ATTACK_STATE);
   pros::delay(150);

   //Move back to the 5th tile edge, and restart the intake 15 inches into the movement.
   chassis.moveToPoint(47.5, 61.5, 750, {.forwards = false, .maxSpeed = 75});
   IntakeMotor.move_velocity(600);
   chassis.waitUntil(5);
   ladybrown.MoveToPoint(LadyBrown::BASE_STATE);

   //Point the robot towards the home side wall, and put the lady brown down.
   chassis.turnToPoint(47.5, 0, 950);
   HookMotor.move_velocity(200);
   

   //Go close to the wall, but exit early so that the robot glides to the last ring.
   chassis.moveToPoint(47.5, -3, 2500, {.forwards = true, .maxSpeed = 50, .earlyExitRange=2});

   //Start the hook at a higher speed rpm
   HookMotor.move_velocity(200);

   // Start at 10 inches into the movement - schedule a check every 5 inches for if the hook is stuck.
   chassis.waitUntil(10);
   for (int i = 12; i<47; i += 5) {
      chassis.waitUntil(i);
      std::cout << "velocity" << HookMotor.get_actual_velocity() << std::endl;
      while (HookMotor.get_actual_velocity() < 25 && !(colorSensor.get_hue() < 30 && colorSensor.get_hue() > 8)) {
         //FIX: The hook is lifted back and then hit into the target to ensure fit.
         HookMotor.move_velocity(-200);
         pros::delay(150);
         HookMotor.move_velocity(200);
         pros::delay(350);
      }
   }

   chassis.waitUntilDone();
   //Wait for two seconds at the edge to ensure rings get put onto the mogo.
   pros::delay(1000);

   //Turn, then Move to the point where the last ring was nudged to collect it for top ring
   chassis.turnToPoint(61, 17, 1000);
   chassis.moveToPoint(61, 17, 1000, {.forwards = true, .maxSpeed = 50, .earlyExitRange=4});


   //Turn away to position the mogo in the corner, waiting to let the hook put all items onto the mogo.
   chassis.turnToHeading(-30, 1000, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE}, false);
   pros::delay(700);
   //Let the last ring go when the hook gets stuck
   HookMotor.move_velocity(-200);
   //Let the mogo go
   LatchControl.retract();

   //Move back a little to ensure the mogo goes into the corner.
   chassis.moveToPoint(64.5, 0, 1200, {.forwards = false, .maxSpeed = 70, .earlyExitRange=1.5}, false);

   // Stop the intake and hook.
   IntakeMotor.brake();
   HookMotor.brake();
   
   //Move to the top edge of the first tile, preparing for alignment. Then move back into the wall to use the distance sensor to reorient.
   chassis.moveToPose(48, 20, -90, 1000, {.forwards = true, .horizontalDrift=9}, false);
   LatchControl.extend();
   chassis.moveToPoint(68, 20, 1350, {.forwards = false}, false);

   // Get the distance to the wall using the distance sensor, convert to inches and add the distance to tracking center (5in).
   // Then, set the new position
   //float new_x = (float)(72 - 8);
   float new_x = (float)(72 - 8);
   std::cout << "Distance: " << new_x << std::endl;
   std::cout << "Distance: " << (float)(72) / (float)10 / (float)2.54 << std::endl;
   std::cout << "Distance: " << distance.get_distance() << std::endl;
   chassis.setPose(new_x, chassis.getPose().y, -90);
   chassis.moveToPoint(chassis.getPose().x-5, chassis.getPose().y, 600, { .minSpeed=60, .earlyExitRange=2}, false);

   //TODO: ADJUST DISTANCE VALUES FOR RESET
   // float new_y = ((float)(distance.get_distance()) / (float)10 / (float)2.54 + (float)6.5 - (float)8.75);
   //chassis.moveToPose(0, 15, -90, 1500, {.horizontalDrift = 8, .minSpeed = 15});  
   
   chassis.turnToPoint(-26, 12.5, 1000, {.forwards=false});
   LatchControl.retract();
   chassis.moveToPoint(-26, 12.5, 5000, {.forwards = false, .minSpeed=50, .earlyExitRange=26});
   chassis.moveToPoint(-26, 12.5, 1000, {.forwards = false, .maxSpeed=45});

   //chassis.moveToPoint(-21, 15, 700, {.forwards = false, .maxSpeed=70}, false);
   chassis.waitUntilDone();
   //Latch the mogo - delays just in case
   LatchControl.extend();
   pros::delay(250);

   //Turn to the above ring - Start intake and hook, and move there
   chassis.turnToPoint(-24, 38.75, 850, {}, false);
   IntakeMotor.move_velocity(600);
   HookMotor.move_velocity(200);
   chassis.moveToPoint(-24, 38.75, 1000);

   // Immediately move to the farthest ring. A couple of other things happen while this is going on
   chassis.moveToPose(-48, 90, 0, 2050, {.horizontalDrift = 8, .lead = 0.54}, true);
   //Checks between 10-45 inches of movement for if the hook got stuck on the mogo flower
   for (int i = 10; i<45; i += 5) {
   chassis.waitUntil(i);
   std::cout << "velocity" << HookMotor.get_actual_velocity() << std::endl;
   //Checks every 5 inches for if the hook gets stuck.
   while (HookMotor.get_actual_velocity() < 25 && !(colorSensor.get_hue() < 30 && colorSensor.get_hue() > 8)) {
      //FIX: The hook is lifted back and then hit into the target to ensure fit.
      HookMotor.move_velocity(-200);
      pros::delay(150);
      HookMotor.move_velocity(200);
      pros::delay(350);
   }
   //Lift up the Lady brown to load onto at 40 inches from the last position.
   }

   //Set the hook to a high-torque rpm to get the best loading possible, waits for the MoveToPose to end.
   chassis.waitUntil(50);

   HookMotor.move_velocity(200);

   chassis.waitUntilDone();   //Turn to a point ~1.5 tiles away from the right neutral stake
   ladybrown.MoveToPoint(LadyBrown::LOAD_STATE);
   chassis.turnToPoint(-43, 60.5, 800, {.forwards=false});

   //Actually move there
   chassis.moveToPoint(-43, 60.5, 1500, {.forwards=false}, true);


   // Wait until 20 inches passed to get to the point behind the lady brown - stop the hook here.


   chassis.waitUntilDone();

   chassis.turnToPoint(-78, 60.5, 660);


   // Move there
   chassis.moveToPoint(-72.5, 60.5, 1020, {.forwards=true, .maxSpeed=75, .minSpeed=50, .earlyExitRange=6}, true);

   // At 18 inches of movement, stop the intake in advan.;;;78yce of the neutral wall stake
   chassis.waitUntil(18);
   IntakeMotor.brake();
   HookMotor.brake();

   chassis.waitUntilDone();

   //Allow the robot to settle, then move the lady brown to score on the neutral stake.
   ladybrown.MoveToPoint(LadyBrown::ATTACK_STATE);

   //Move back to the 5th tile edge, and restart the intake 15 inches into the movement.
   chassis.moveToPoint(-47, 60.5, 750, {.forwards = false, .maxSpeed = 75});
   IntakeMotor.move_velocity(600);
   chassis.waitUntil(5);
   ladybrown.MoveToPoint(LadyBrown::BASE_STATE);


   //Point the robot towards the home side wall, and put the lady brown down.
   chassis.turnToPoint(-47, 0, 950);
   HookMotor.move_velocity(200);

   //Go close to the wall, but exit early so that the robot glides to the last ring.
   chassis.moveToPoint(-47, 0, 2750, {.forwards = true, .maxSpeed = 60, .minSpeed=30, .earlyExitRange=4});

   //Start the hook at a higher speed rpm
   HookMotor.move_velocity(200);

   // Start at 10 inches into the movement - schedule a check every 5 inches for if the hook is stuck.
   chassis.waitUntil(10);
   for (int i = 12; i<47; i += 5) {
      chassis.waitUntil(i);
      std::cout << "velocity" << HookMotor.get_actual_velocity() << std::endl;
      while (HookMotor.get_actual_velocity() < 25 && !(colorSensor.get_hue() < 30 && colorSensor.get_hue() > 8)) {
         //FIX: The hook is lifted back and then hit into the target to ensure fit.
         HookMotor.move_velocity(-200);
         pros::delay(150);
         HookMotor.move_velocity(200);
         pros::delay(350);
      }
   }

   chassis.waitUntilDone();
   //Wait for two seconds at the edge to ensure rings get put onto the mogo.
   pros::delay(1000);

   //Turn, then Move to the point where the last ring was nudged to collect it for top ring
   chassis.turnToPoint(-62, 17, 1000);
   chassis.moveToPoint(-62, 17, 2000, {.forwards = true, .maxSpeed = 50, .earlyExitRange=4});


   //Turn away to position the mogo in the corner, waiting to let the hook put all items onto the mogo.
   chassis.turnToHeading(30, 1000, {}, false);
   pros::delay(1000);
   //Let the last ring go when the hook gets stuck
   HookMotor.move_velocity(-200);
   pros::delay(200);
   //Let the mogo go
   LatchControl.retract();

   //Move back a little to ensure the mogo goes into the corner.
   chassis.moveToPoint(-62.5, 2, 1000, {.forwards = false, .maxSpeed = 50, .earlyExitRange=1.5}, false);

   // Stop the intake and hook.
   IntakeMotor.brake();
   HookMotor.brake();
   
   //Move to the top edge of the first tile, preparing for alignment. Then move back into the wall to use the distance sensor to reorient.
   chassis.moveToPoint(-15, 110.5, 7000, {.forwards = true, .maxSpeed = 100, .minSpeed=40, .earlyExitRange=6},  true);
   //chassis.moveToPoint(70, 132.5, 1500);

   chassis.moveToPose(-70, 128, -75, 5000);

   chassis.moveToPoint(-6, 114, 3000, {.forwards=false}, false);

   SweeperControl.extend();

   chassis.turnToPoint(68, 125, 1000);

   chassis.moveToPoint(68, 125, 3000, {.forwards=true, .minSpeed=30, .earlyExitRange=6});

   chassis.waitUntil(10);
   SweeperControl.retract();
}
