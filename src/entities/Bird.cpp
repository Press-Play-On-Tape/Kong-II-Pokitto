#include "Bird.h"

#include "../utils/Enums.h"

Bird::Bird() { }

uint16_t Bird::getPosition() {

    return this->position;

}

uint8_t Bird::getXPosition(ViewSize viewSize) {

    uint8_t x = Coordinates::Bird[(this->position * 3)];

    if (viewSize == ViewSize::Normal) {
        return x + VIEW_NORMAL_X_OFFSET;
    }
    else {
        return (x - 9) * 2;
    }

}

uint8_t Bird::getYPosition(ViewSize viewSize, uint8_t yOffset) {

    uint8_t y = Coordinates::Bird[(this->position * 3) + 1];
    
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

uint8_t Bird::getImage() {

    return pgm_read_byte(&Coordinates::Bird[(this->position * 3) + 2]);

}

bool Bird::isEnabled() {

    return this->enabled;

}

void Bird::setEnabled(bool enabled) {

    this->enabled = enabled;
    this->position = 0;

}

void Bird::setPosition(uint16_t position) {

    this->position = position;

}

void Bird::updatePosition() {

    if (!this->enabled) return;

    this->position++;

    uint8_t x = pgm_read_byte(&Coordinates::Bird[(this->position * 3)]);
    uint8_t y = pgm_read_byte(&Coordinates::Bird[(this->position * 3) + 1]);

    if (x == 0 && y == 0) {

    this->enabled = false;
    this->position = 0;

    }

}

Rect Bird::getRect(ViewSize viewSize, uint8_t yOffset, GameMode mode) {

    uint16_t x = this->getXPosition(viewSize);
    uint8_t y = this->getYPosition(viewSize, yOffset);

    if (viewSize == ViewSize::Normal) {

        switch (static_cast<BirdImage>(this->getImage())) {

            case BirdImage::Bird_Upright:
                if (mode == GameMode::Easy) {
                    return Rect{x + 2, y + 2, 4, 7 };
                }
                else {
                    return Rect{x + 1, y + 1, 6, 9 };
                }

            case BirdImage::Bird_00:
            case BirdImage::Bird_02:
                if (mode == GameMode::Easy) {
                    return Rect{x + 2, y + 2, 8, 3 };
                }
                else {
                    return Rect{x + 1, y + 1, 10, 5 };
                }

            case BirdImage::Bird_01:
            case BirdImage::Bird_03:
                if (mode == GameMode::Easy) {
                    return Rect{x + 2, y + 4, 8, 2 };
                }
                else {
                    return Rect{x + 1, y + 3, 10, 4 };
                }

            case BirdImage::Bird_Turn_00:
            case BirdImage::Bird_Turn_05:
                if (mode == GameMode::Easy) {
                    return Rect{x + 2, y + 2, 7, 5 };
                }
                else {
                    return Rect{x + 1, y + 1, 9, 7 };
                }

            case BirdImage::Bird_Turn_01:
                if (mode == GameMode::Easy) {
                    return Rect{x + 5, y + 2, 3, 8 };
                }
                else {
                    return Rect{x + 4, y + 1, 5, 10 };
                }

            case BirdImage::Bird_Turn_02:
            case BirdImage::Bird_Turn_03:
                if (mode == GameMode::Easy) {
                    return Rect{x + 2, y + 2, 7, 5 };
                }
                else {
                    return Rect{x + 1, y + 1, 9, 7 };
                }

            case BirdImage::Bird_Turn_04:
                if (mode == GameMode::Easy) {
                    return Rect{x + 5, y + 2, 3, 8 };
                }
                else {
                    return Rect{x + 3, y + 1, 5, 10 };
                }

            default: return Rect{ 0, 0, 0, 0 };

        }

    }
    else {

        switch (static_cast<BirdImage>(this->getImage())) {

            case BirdImage::Bird_Upright:
                if (mode == GameMode::Easy) {
                    return Rect{x + 4, y + 4, 8, 14 };
                }
                else {
                    return Rect{x + 2, y + 2, 12, 18 };
                }

            case BirdImage::Bird_00:
            case BirdImage::Bird_02:
                if (mode == GameMode::Easy) {
                    return Rect{x + 4, y + 4, 16, 6 };
                }
                else {
                    return Rect{x + 2, y + 2, 20, 10 };
                }

            case BirdImage::Bird_01:
            case BirdImage::Bird_03:
                if (mode == GameMode::Easy) {
                    return Rect{x + 4, y + 8, 16, 4 };
                }
                else {
                    return Rect{x + 2, y + 6, 20, 8 };
                }

            case BirdImage::Bird_Turn_00:
            case BirdImage::Bird_Turn_05:
                if (mode == GameMode::Easy) {
                    return Rect{x + 4, y + 4, 14, 10 };
                }
                else {
                    return Rect{x + 2, y + 2, 18, 14 };
                }

            case BirdImage::Bird_Turn_01:
                if (mode == GameMode::Easy) {
                    return Rect{x + 10, y + 4, 6, 16 };
                }
                else {
                    return Rect{x + 8, y + 2, 10, 20 };
                }

            case BirdImage::Bird_Turn_02:
            case BirdImage::Bird_Turn_03:
                if (mode == GameMode::Easy) {
                    return Rect{x + 4, y + 4, 14, 10 };
                }
                else {
                    return Rect{x + 2, y + 2, 18, 14 };
                }

            case BirdImage::Bird_Turn_04:
                if (mode == GameMode::Easy) {
                    return Rect{x + 10, y + 4, 6, 16 };
                }
                else {
                    return Rect{x + 6, y + 2, 10, 20 };
                }

            default: return Rect{ 0, 0, 0, 0 };

        }

    }

}