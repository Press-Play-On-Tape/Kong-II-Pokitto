#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"

class Clapper {

    public:

        Clapper();

        // Properties ..

        int16_t getXPosition(ViewSize viewSize);
        uint8_t getYPosition(ViewSize viewSize, uint8_t yOffset);
        uint8_t getImage(ViewSize viewSize);
        bool isEnabled();

        void setEnabled(ViewSize viewSize, bool enabled);
        void setY(ViewSize viewSize, uint8_t y);


        // Methods

        void updatePosition(ViewSize viewSize);
        Rect getRect(ViewSize viewSize, uint8_t yOffset, GameMode mode);

    protected:

        bool enabled = false;
        int16_t x;
        uint8_t y;

};

