#include "Kong.h"

#include "../utils/Enums.h"

Kong::Kong() { }

uint8_t Kong::getXPosition(ViewSize viewSize) {

    if (viewSize == ViewSize::Normal) {

        if (!this->enabled) {

            return 52 + VIEW_NORMAL_X_OFFSET;

        }
        else {
    
            return Coordinates::Kong_Exit[(this->position * 3)] + VIEW_NORMAL_X_OFFSET;

        }

    }
    else {

        if (!this->enabled) {

            return 76;

        }
        else {
    
            return (Coordinates::Kong_Exit[(this->position * 3)] * 2) - 14;

        }

    }

}

KongImage Kong::getImage() {

    if (!this->enabled) {

        return KongImage::Normal;

    }
    else {
 
        return static_cast<KongImage>(Coordinates::Kong_Exit[(this->position * 3) + 2]);

    }

}


int8_t Kong::getYPosition(ViewSize viewSize, uint8_t yOffset) {

    if (viewSize == ViewSize::Normal) {
            
        if (!this->enabled) {

            return 1 + VIEW_NORMAL_Y_UPPER_OFFSET;

        }
        else {
    
            int8_t y = Coordinates::Kong_Exit[(this->position * 3) + 1];
            return y + VIEW_NORMAL_Y_UPPER_OFFSET + (this->position == 0 ? 1 : 0);

        }

    }
    else {
            
        if (!this->enabled) {

            return 1 - yOffset;

        }
        else {
    
            int8_t y = Coordinates::Kong_Exit[(this->position * 3) + 1] * 2;
            return y - yOffset + (this->position == 0 ? 2 : 0);

        }

    }

}

bool Kong::getChain(uint8_t index) {

    return this->chains[index];

}

bool Kong::getFlashChain(uint8_t index) {

    return this->flash[index];

}

bool Kong::isEnabled() {

    return this->enabled;

}

bool Kong::getExit() {

    return this->exit;

}

bool Kong::getEnabled() {

    return this->enabled;

}

void Kong::setEnabled(bool enabled) {

    this->enabled = enabled;

}

void Kong::setChain(uint8_t index, bool value) {

    this->chains[index] = value;

}

void Kong::setFlashChain(uint8_t index, bool value) {

    this->flash[index] = value;
    if (value) this->counter = 96;

}

void Kong::setChains(bool value) {

    for (uint8_t x =  0; x < NUMBER_OF_CHAINS; x++) {
        this->chains[x] = value;
    }

}

void Kong::setExit(bool value) {

    this->exit = value;

}

bool Kong::updateChains() {

    if (this->counter > 0) {

        this->counter--;

        if (this->counter == 0) {

            uint8_t count = 0;

            for (uint8_t x = 0; x < NUMBER_OF_CHAINS; x++) {

                if (!this->chains[x]) {
                
                    count++;
                
                }

                if (this->flash[x]) {

                    this->chains[x] = false;
                    this->flash[x] = false;
                    count++;

                }

            }

            if (count == 4) { 

                this->enabled = true;    
                return true; 
                
            }

        }

    }

    return false;

}

bool Kong::updatePosition(ViewSize viewSize) {

    if (!this->enabled) return false;

    this->position++;

    uint8_t x = Coordinates::Kong_Exit[(this->position * 3)];
    uint8_t y = Coordinates::Kong_Exit[(this->position * 3) + 1];

    if (viewSize == ViewSize::Large) {

        x = x * 2;
        y = y * 2;

    }

    if (x == 0 && y == 0) {

        this->enabled = false;
        this->position = 0;

        for (uint8_t x = 0; x < NUMBER_OF_CHAINS; x++) {

            this->chains[x] = true;

        }

        return true;

    }

    return false;

}

bool Kong::getDisplayChain(uint8_t index) {

    return this->chains[index] && (!this->flash[index] || ((this->counter / 16) % 2));

}

void Kong::reset() {

    this->enabled = true;
    this->exit = false;

    this->setChains(true);

    #ifdef ONE_KEY_ONLY
    this->setChains(false);
    this->setChain(3, true);
    #endif

    #ifdef TWO_KEYS_ONLY
    this->setChains(false);
    this->setChain(1, true);
    this->setChain(2, true);
    #endif

}