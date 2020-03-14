#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"
#include "../map/Coordinates.h"

class Bird {

    public:

        Bird();

        // Properties ..

        uint16_t getPosition();
        uint8_t getXPosition(ViewSize viewSize);
        uint8_t getYPosition(ViewSize viewSize, uint8_t yOffset);
        uint8_t getImage();
        bool isEnabled();

        void setPosition(uint16_t position);
        void setEnabled(bool enabled);


        // Methods

        void updatePosition();
        Rect getRect(ViewSize viewSize, uint8_t yOffset, GameMode mode);

    protected:

        bool enabled = false;
        uint16_t position = 0;
        uint8_t counter = 0;

};

