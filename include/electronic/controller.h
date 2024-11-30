#pragma once

namespace Robot {

class Controller {
public:
   void notifier();

   void switchControl();

   static void notify_motor_disconnect(void *param);

   Controller();
};
} // namespace Robot