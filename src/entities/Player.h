#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"
#include "../map/Coordinates.h"

class Player {

    public:

        Player();


        // Properties ..

        uint16_t getPosition();
        uint8_t getJumpPosition();
        uint8_t getXPosition(ViewSize viewSize, bool updatePrevPosition);
        uint8_t getYPosition(ViewSize viewSize);
        uint8_t getMovements();
        uint8_t getYOffset();
        bool isDead();
        bool isFalling();
        bool getExit();

        void setPosition(ViewSize viewSize, uint16_t position);
        void setJumpPosition(uint8_t jumpPosition);
        void setDead(bool dead);
        void setFalling(bool falling);
        void setExit(bool dead);


        // Methods

        uint8_t getImage();
        uint8_t getImage(bool update);

        void incPlayerPosition(ViewSize viewSize);
        void decPlayerPosition(ViewSize viewSize, bool exitSequence);

        bool canMove(Movements movement);
        void updateJump();
        void startJump();
        bool isJumping();
        bool atTopOfJump();
        bool canGrabChain();
        void reset(ViewSize viewSize);

        Rect getRect(ViewSize viewSize);

    protected:

        uint16_t position;
        uint8_t jumpPosition;
        uint8_t movements;

        uint8_t prevXPosition;
        uint8_t runCounter;
        uint8_t prevImage;
        Movements runMovement = Movements::Right;

        bool dead = false;
        bool falling = false;
        bool exit = false;
        Coordinates::PlayerData playerData;

};

