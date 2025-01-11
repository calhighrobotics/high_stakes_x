#pragma once

namespace Robot {

class Controller {
public:
   void notifier();

   void switchControl();

   /**
    * @brief PROS task that gives feedback to the driver about disconnected
    * motors.
    *
    * When a motor disconnects, this task will notify the driver using haptic
    * and visual feedback. The controler will vibrate in three short pulses if a
    * motor disconnects, and will vibrate in one long pulse if a motor
    * reconnects. The LCD screen is also updated with the current disconnected
    * motors. When the connection state of all motors remains the same, the task
    * won't give feedback to the controller.
    *
    */
   static void notify_motor_disconnect(void *param);

   Controller();
};
} // namespace Robot