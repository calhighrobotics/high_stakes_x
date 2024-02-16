#pragma once

namespace Robot {

    class Puncher {
        public:
            void run();
            void setDistancePuncher(bool punch);
        private:
            int toShoot();
            bool distancePuncher;
    };
}