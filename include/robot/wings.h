#pragma once


namespace Robot {
class Wings {
    public:
        void run();
        void setState(bool wingState);
        bool getState();
    private:
        bool state;
};

}