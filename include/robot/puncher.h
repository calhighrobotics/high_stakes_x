#pragma once

namespace Robot {

    class Puncher {
        public:
            void run(int autonVal);
            void setDistancePuncher(bool punch);
        private:
            int toShoot();
            bool distancePuncher;
    };
}