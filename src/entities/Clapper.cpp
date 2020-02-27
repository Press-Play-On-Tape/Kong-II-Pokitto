#include "Clapper.h"

#include "../utils/Enums.h"

Clapper::Clapper() { }

int16_t Clapper::getXPosition(ViewSize viewSize) {

    if (viewSize == ViewSize::Normal) {
        return this->x + VIEW_NORMAL_X_OFFSET;
    }
    else {
        return this->x;
    }

}

uint8_t Clapper::getYPosition(ViewSize viewSize, uint8_t yOffset) {

    if (viewSize == ViewSize::Normal) {

        if (this->y < 64) {
            return this->y + VIEW_NORMAL_Y_UPPER_OFFSET;
        }
        else {
            return this->y + VIEW_NORMAL_Y_LOWER_OFFSET;
        }

    }
    else {
        return this->y - yOffset;
    }

}

uint8_t Clapper::getImage(ViewSize viewSize) {

    int16_t x = this->getXPosition(viewSize);
    return (x % 8 < 4 ? 1 : 0);

}

bool Clapper::isEnabled() {

    return this->enabled;

}

void Clapper::setEnabled(bool enabled) {

    this->enabled = enabled;
    this->x = 126;

}

void Clapper::setY(uint8_t y) {

    this->y = y;

}

void Clapper::updatePosition() {

    if (x > -7) x--;
    if (x == -7) enabled = false;

}

Rect Clapper::getRect(uint8_t yOffset, GameMode mode) {

    if (mode == GameMode::Easy) {
        return Rect{this->x + 2, this->y - yOffset + 2, 5, 3 };
    }
    else {
        return Rect{this->x + 1, this->y - yOffset + 1, 7, 5 };
    }

}
