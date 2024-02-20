#pragma once

namespace Robot {

    class Puncher {
        public:
            void run(int autonVal);
            void setDistancePuncher(bool punch);
            void PuncherSwitch();
        private:
            int toShoot();
            bool distancePuncher;
    };
}