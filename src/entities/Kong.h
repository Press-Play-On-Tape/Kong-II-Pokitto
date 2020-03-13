#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"
#include "../map/Coordinates.h"

class Kong {

    public:

        Kong();

        KongImage getImage();
        uint16_t getPosition();
        uint8_t getXPosition(ViewSize viewSize);
        int8_t getYPosition(ViewSize viewSize, uint8_t yOffset);
        bool getChain(uint8_t index);
        bool getFlashChain(uint8_t index);
        bool getExit();
        bool getEnabled();

        bool isEnabled();
        void setChain(uint8_t index, bool value);
        void setFlashChain(uint8_t index, bool value);
        void setChains(bool value);
        void setExit(bool value);
        void setEnabled(bool value);

        bool updateChains();                                    // Returns true if all 4 chains gone.
        bool updatePosition(ViewSize viewSize);                 // Returns tru if exit sequence is complete.
        bool getDisplayChain(uint8_t index);
        void reset();

    protected:

        bool chains[4] = { true, true, true, true };  
        bool flash[4] = { false, false, false, false };

        bool exit = false;
        bool enabled = false;
        uint8_t counter = 0;
        uint8_t position = 0;

};

