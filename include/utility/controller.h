#pragma once

namespace Robot {
/**
 * @brief Contains members related to modifying the controller screen.
 */
class Controller {
public:
   /**
    * @brief PROS task that gives feedback to the driver about disconnected
    * motors.
    *
    * If a motor is disconnected, this task will notify the driver using haptic
    * and visual feedback. The controler will vibrate in three short pulses if a
    * motor disconnects, and will vibrate in one long pulse if a motor
    * reconnects. The LCD screen is also updated with the current disconnected
    * motors. When the connection state of all motors remains the same, no
    * feedback is given.
    *
    */
   void static notify_motor_disconnect(void *param);
};
} // namespace Robot