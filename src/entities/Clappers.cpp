#include "Clappers.h"

#include "../utils/Enums.h"

Clappers::Clappers() { }

Clapper & Clappers::getClapper(uint8_t index) {

    return this->clappers[index];

}

void Clappers::updatePositions(ViewSize viewSize) {

    for (auto &clapper : this->clappers) {

        if (clapper.isEnabled()) {

            clapper.updatePosition(viewSize);
        }

    }

    if (this->delay > 0) {
        
        this->delay--;

    }
    else {

        this->launchClapper(viewSize);

    }

}


void Clappers::setDelayMax(uint8_t delayMax, bool updateDelay) {

    if (updateDelay) this->delay = random(0, delayMax / 2);
    this->delayMax = delayMax;

}

void Clappers::launchClapper(ViewSize viewSize) {

    for (auto &clapper : this->clappers) {

        if (!clapper.isEnabled()) {

            clapper.setEnabled(viewSize, true);
            this->delay = random(this->delayMax / 2, this->delayMax);
            return;

        }

    }

}

void Clappers::reset(ViewSize viewSize, uint8_t y) {

    for (auto &clapper : this->clappers) {

        clapper.setEnabled(viewSize, false);
        clapper.setY(viewSize, y);

    }

}
