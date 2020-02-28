#include "Clapper.h"

#include "../utils/Enums.h"

Clapper::Clapper() { }

int16_t Clapper::getXPosition(ViewSize viewSize) {

    if (viewSize == ViewSize::Normal) {
        return this->x + VIEW_NORMAL_X_OFFSET;
    }
    else {
        return this->x - 18;
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

void Clapper::setEnabled(ViewSize viewSize, bool enabled) {

    this->enabled = enabled;

    if (viewSize == ViewSize::Normal) {
        this->x = 126;
    }
    else {
        this->x = 126 * 2;
    }

}

void Clapper::setY(ViewSize viewSize, uint8_t y) {

    if (viewSize == ViewSize::Normal) {

        this->y = y;

    }
    else {

        this->y = y * 2;

    }

}

void Clapper::updatePosition(ViewSize viewSize) {

    if (viewSize == ViewSize::Normal) {

        if (x > -7) x--;
        if (x == -7) enabled = false;

    }
    else {

        if (x > -14) x = x - 2;
        if (x == -14) enabled = false;

    }

}

Rect Clapper::getRect(ViewSize viewSize, uint8_t yOffset, GameMode mode) {

    int16_t x = this->getXPosition(viewSize);
    uint8_t y = this->getYPosition(viewSize, yOffset);

    if (viewSize == ViewSize::Normal) {

        if (mode == GameMode::Easy) {
            return Rect{x + 2, y + 2, 5, 3 };
        }
        else {
            return Rect{x + 1, y + 1, 7, 5 };
        }

    }
    else {

        if (mode == GameMode::Easy) {
            return Rect{x + 4, y + 4, 10, 6 };
        }
        else {
            return Rect{x + 2, y + 2, 14, 10 };
        }

    }

}
