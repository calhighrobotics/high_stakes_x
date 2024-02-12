#pragma once

namespace Robot {

    class Puncher {
        public:
            void run();
        private:
            int toShoot();
            bool distancePuncher;
    };
}