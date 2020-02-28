#include "Key.h"

#include "../utils/Enums.h"

Key::Key() { }

uint8_t Key::getPosition() {

    return this->position;

}

uint8_t Key::getXPosition(ViewSize viewSize) {

    if (viewSize == ViewSize::Normal) {
            
        if (this->position == 0) {

            switch (this->keyLocation) {

                case KeyLocation::LowerPosition:
                    return 11 + VIEW_NORMAL_X_OFFSET;

                case KeyLocation::UpperPosition:
                    return 12 + VIEW_NORMAL_X_OFFSET;

                case KeyLocation::Position_00:
                    return 34 + VIEW_NORMAL_X_OFFSET;

                case KeyLocation::Position_01:
                    return 53 + VIEW_NORMAL_X_OFFSET;

                case KeyLocation::Position_02:
                    return 72 + VIEW_NORMAL_X_OFFSET;

                case KeyLocation::Position_03:
                    return 91 + VIEW_NORMAL_X_OFFSET;

                default:
                    return 0;

            }

        }
        else {

            return this->path[(this->position * 3)] + VIEW_NORMAL_X_OFFSET;

        }

    }
    else {
                   
        if (this->position == 0) {

            switch (this->keyLocation) {

                case KeyLocation::LowerPosition:
                    return 7; //11;

                case KeyLocation::UpperPosition:
                    return 9; //12;

                case KeyLocation::Position_00:
                    return 54; //34;

                case KeyLocation::Position_01:
                    return 92; //53;

                case KeyLocation::Position_02:
                    return 130; //72;

                case KeyLocation::Position_03:
                    return 168; //91;

                default:
                    return 0;

            }

        }
        else {

            return (this->path[(this->position * 3)] * 2) - 18;

        }

    }

}

uint8_t Key::getYPosition(ViewSize viewSize, uint8_t yOffset) {

    if (viewSize == ViewSize::Normal) {

        if (this->position == 0) {

            switch (this->keyLocation) {

                case KeyLocation::LowerPosition:
                    return 90 + VIEW_NORMAL_Y_LOWER_OFFSET;

                case KeyLocation::UpperPosition:
                    return 35 + VIEW_NORMAL_Y_UPPER_OFFSET;

                case KeyLocation::Position_00:
                case KeyLocation::Position_01:
                case KeyLocation::Position_02:
                case KeyLocation::Position_03:
                    return 12 + VIEW_NORMAL_Y_UPPER_OFFSET;

                default:
                    return 0;

            }

        }
        else {

            uint8_t y = pgm_read_byte(&this->path[(this->position * 3) + 1]);

            if (y < 64) {
                return y + VIEW_NORMAL_Y_UPPER_OFFSET;
            }
            else {
                return y + VIEW_NORMAL_Y_LOWER_OFFSET;
            }

        }

    }
    else {

        if (this->position == 0) {

            switch (this->keyLocation) {

                case KeyLocation::LowerPosition:
                    return 180 - yOffset; //90

                case KeyLocation::UpperPosition:
                    return 70 - yOffset; //35

                case KeyLocation::Position_00:
                case KeyLocation::Position_01:
                case KeyLocation::Position_02:
                case KeyLocation::Position_03:
                    return 24 - yOffset; 24;//

                default:
                    return 0;

            }

        }
        else {

            uint8_t y = this->path[(this->position * 3) + 1];
            return (y * 2) - yOffset;

        }
        
    }

}

uint8_t Key::getImage() {

    if (this->position == 0) {

        switch (this->keyLocation) {

            case KeyLocation::LowerPosition:
            case KeyLocation::UpperPosition:
                return NO_IMAGE;

            case KeyLocation::Position_00:
            case KeyLocation::Position_01:
            case KeyLocation::Position_02:
            case KeyLocation::Position_03:
                return static_cast<uint8_t>(KeyImage::Position_04);

            default:    
                return 0;

        }

    }
    else {

        return pgm_read_byte(&this->path[(this->position * 3) + 2]);

    }

}

KeyLocation Key::getKeyLocation() {

    return this->keyLocation;

}

bool Key::isEnabled() {

    return this->enabled;

}

void Key::setEnabled(bool enabled) {

    this->enabled = enabled;
    this->position = 0;

}

void Key::setFlash(bool value) {

    this->flash = value;
    if (this->flash) this->counter = 96;

}

void Key::setPath(uint8_t const *path) {

    this->path = path;
    this->enabled = true;
    this->position = 0;
}

void Key::setKeyLocation(KeyLocation keyLocation) {

    this->keyLocation = keyLocation;

}

void Key::updatePosition() {

    if (this->counter > 0) {
        
        this->counter--;

        if (this->counter == 0) {

            this->flash = false;
            this->keyLocation = KeyLocation::LowerPosition;
            this->position = 0;
            return;

        }

    }

    if (!this->enabled) return;

    this->position++;

    uint8_t x = pgm_read_byte(&this->path[(this->position * 3)]);
    uint8_t y = pgm_read_byte(&this->path[(this->position * 3) + 1]);

    if (x == 0 && y == 0) {

        switch (this->keyLocation) {

            case KeyLocation::LowerPosition:  
                this->keyLocation = KeyLocation::UpperPosition;
                break;

            case KeyLocation::UpperPosition:  
                {
                  KeyLocation keyLocation = static_cast<KeyLocation>(pgm_read_byte(&this->path[(this->position * 3) + 2]));
                  this->keyLocation = keyLocation;
                }
                break;

            default: break;

        }

        this->enabled = false;
        this->position = 0;

    }

}

Rect Key::getRect(uint8_t yOffset) {

    int8_t x = pgm_read_byte(&this->path[(this->position * 3)]);
    uint8_t y = pgm_read_byte(&this->path[(this->position * 3) + 1]) - yOffset;

    return Rect{x, y, 8, 8 };

}


bool Key::getDisplay() {

    return !this->flash || ((this->counter / 16) % 2);

}