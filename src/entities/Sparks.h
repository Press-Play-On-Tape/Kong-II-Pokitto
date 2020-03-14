#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"
#include "Spark.h"

class Sparks {

    public:

        Sparks();

        Spark & getSpark(uint8_t index);

        void updatePositions();
        void setDelayMax(uint8_t delayMax, bool updateDelay);
        void launchSpark();
        void reset(uint8_t const *path);

    protected:

        Spark sparks[4];
        uint8_t delay;
        uint8_t delayMax;

};

