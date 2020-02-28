#pragma once

#include "Pokitto.h"
#include "../Utils/Enums.h"
#include "Clapper.h"

class Clappers {

    public:

        Clappers();

        Clapper & getClapper(uint8_t index);

        void updatePositions(ViewSize viewSize);
        void setDelayMax(uint8_t delayMax, bool updateDelay);
        void launchClapper(ViewSize viewSize);
        void reset(ViewSize viewSize, uint8_t y);

    protected:

        Clapper clappers[4];
        uint8_t delay;
        uint8_t delayMax;

};

