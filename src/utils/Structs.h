#pragma once

#include "Pokitto.h"
#include "Enums.h"

struct SplashScreenStateVars {

    uint8_t counter = 0;

};

struct TitleScreenStateVars {

    uint8_t position = 0;

};

struct PlayGameStateVars {

    uint8_t introDelay;
    uint8_t preventJumpDelay;   // Used to prevent a jump if the A button is pressed to start game.
    uint8_t frameRate = FRAME_RATE_MIN;

    bool exitSequence = false;
    
    bool playing = false;
    bool paused = false;   

    uint8_t clappersLowerDelay = CLAPPERS_LOWER_MAX_EASY;
    uint8_t clappersUpperDelay = CLAPPERS_UPPER_MAX_EASY;
    uint8_t sparksLowerDelay = SPARKS_LOWER_MAX_EASY;
    uint8_t sparksUpperDelay = SPARKS_UPPER_MAX_EASY;
    uint16_t birdsDelay = BIRDS_MAX_EASY;
    uint8_t pauseMenu = 0;
    
    Player player;
    Kong kong;
    Clappers upperClappers;
    Clappers lowerClappers;
    Sparks upperSparks;
    Sparks lowerSparks;
    Birds birds;
    Key key;

};