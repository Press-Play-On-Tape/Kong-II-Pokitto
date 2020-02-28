#pragma once

#include "Pokitto.h"
#include "../Utils/Enums.h"
#include "../Utils/Utils.h"
#include "../map/Coordinates.h"

class Spark {

    public:

        Spark();

        // Properties ..

        uint8_t getPosition();
        uint8_t getXPosition(ViewSize viewSize);
        uint8_t getYPosition(ViewSize viewSize, uint8_t yOffset);
        uint8_t getImage();
        bool isEnabled();

        void setPosition(uint8_t position);
        void setEnabled(bool enabled);
        void setPath(uint8_t const *path);


        // Methods

        void updatePosition();
        Rect getRect(ViewSize viewSize, uint8_t yOffset, GameMode mode);

    protected:

        bool enabled = false;
        uint8_t position = 0;
        uint8_t counter = 0;
        uint8_t const *path = nullptr; 

};

