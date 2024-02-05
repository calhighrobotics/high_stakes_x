#pragma once


namespace Robot {
class Wings {
    public:
        void check();
        void setState(bool wingState);
        bool getState();
    private:
        bool state;
};

}