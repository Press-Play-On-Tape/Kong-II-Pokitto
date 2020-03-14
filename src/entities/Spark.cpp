#include "Spark.h"

#include "../utils/Enums.h"

Spark::Spark() { }

uint8_t Spark::getPosition() {

    return this->position;

}

uint8_t Spark::getXPosition(ViewSize viewSize) {

    uint8_t x = this->path[(this->position * 3)];

    if (viewSize == ViewSize::Normal) {
        return x + VIEW_NORMAL_X_OFFSET;
    }
    else {
        return (x - 9) * 2;
    }

}

uint8_t Spark::getYPosition(ViewSize viewSize, uint8_t yOffset) {

    uint8_t y = this->path[(this->position * 3) + 1];
    
    if (viewSize == ViewSize::Normal) {

        if (y < 64) {
            return y + VIEW_NORMAL_Y_UPPER_OFFSET;
        }
        else {
            return y + VIEW_NORMAL_Y_LOWER_OFFSET;
        }

    }
    else {
        return (y * 2) - yOffset;
    }

}

uint8_t Spark::getImage() {

    return pgm_read_byte(&this->path[(this->position * 3) + 2]);

}

bool Spark::isEnabled() {

    return this->enabled;

}

void Spark::setEnabled(bool enabled) {

    this->enabled = enabled;
    this->position = 0;

}

void Spark::setPath(uint8_t const *path) {

    this->path = path;

}

void Spark::setPosition(uint8_t position) {

    this->position = position;

}

void Spark::updatePosition() {

    if (!this->enabled) return;

    this->position++;

    uint8_t x = pgm_read_byte(&this->path[(this->position * 3)]);
    uint8_t y = pgm_read_byte(&this->path[(this->position * 3) + 1]);

    if (x == 0 && y == 0) {

        this->enabled = false;
        this->position = 0;

    }
  
}

Rect Spark::getRect(ViewSize viewSize, uint8_t yOffset, GameMode mode) {

    uint8_t x = this->getXPosition(viewSize);
    uint8_t y = this->getYPosition(viewSize, yOffset);

    if (viewSize == ViewSize::Normal) {

        if (mode == GameMode::Easy) {
            return Rect{x + 2, y + 2, 2, 1 };
        }
        else {
            return Rect{x + 1, y + 1, 4, 3 };
        }

    }
    else {

        if (mode == GameMode::Easy) {
            return Rect{x + 6, y + 6, 4, 2 };
        }
        else {
            return Rect{x + 4, y + 4, 8, 6 };
        }

    }

}
