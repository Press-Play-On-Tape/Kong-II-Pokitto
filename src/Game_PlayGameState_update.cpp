#include "Game.h"
#include "Pokitto.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;



// ----------------------------------------------------------------------------
//    Handle state updates .. 
//
void Game::playGame_Update() { 

    if (!playGame_GetPaused() && !this->playGameVars.player.isDead()) {


        // Handle player movements ..

        if (this->playGameVars.playing) {

            this->playGameVars.player.getXPosition(this->cookie->viewSize, true);

            if (!this->playGameVars.player.isJumping() && !this->playGameVars.player.isFalling() && !this->playGameVars.exitSequence) {


                // If the player is running from right to left, the controls are reversed ..

                if (this->playGameVars.player.canMove(Movements::Reverse)) {

                    if ((PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 1)) && this->playGameVars.player.canMove(Movements::Left)) {
                        this->playGameVars.player.incPlayerPosition(this->cookie->viewSize);
                    }

                    if ((PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1)) && this->playGameVars.player.canMove(Movements::Right)) {
                        this->playGameVars.player.decPlayerPosition(this->cookie->viewSize, false);
                    }

                }
                else {

                    if ((PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1)) && this->playGameVars.player.canMove(Movements::Right)) {
                        this->playGameVars.player.incPlayerPosition(this->cookie->viewSize);
                    }

                    if ((PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 1)) && this->playGameVars.player.canMove(Movements::Left)) {
                        this->playGameVars.player.decPlayerPosition(this->cookie->viewSize, false);
                    }

                }

                if ((PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 1)) && this->playGameVars.player.canMove(Movements::Down)) {
                    this->playGameVars.player.decPlayerPosition(this->cookie->viewSize, false);
                }

                if ((PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 1)) && this->playGameVars.player.canMove(Movements::Up)) {
                    
                    this->playGameVars.player.incPlayerPosition(this->cookie->viewSize);

                    if (this->playGameVars.player.getPosition() == PLAYER_CHAIN_0_END - 1 && this->playGameVars.key.getKeyLocation() == KeyLocation::Position_00 && !this->playGameVars.kong.getFlashChain(0)) {

                        playGame_CheckLastKey(0);
                        
                    }
                    else if (this->playGameVars.player.getPosition() == PLAYER_CHAIN_1_END - 1 && this->playGameVars.key.getKeyLocation() == KeyLocation::Position_01 && !this->playGameVars.kong.getFlashChain(1)) {

                        playGame_CheckLastKey(1);
                        
                    }
                    else if (this->playGameVars.player.getPosition() == PLAYER_CHAIN_2_END - 1 && this->playGameVars.key.getKeyLocation() == KeyLocation::Position_02 && !this->playGameVars.kong.getFlashChain(2)) {

                        playGame_CheckLastKey(2);
                        
                    }
                    else if (this->playGameVars.player.getPosition() == PLAYER_CHAIN_3_END - 1 && this->playGameVars.key.getKeyLocation() == KeyLocation::Position_03 && !this->playGameVars.kong.getFlashChain(3)) {

                        playGame_CheckLastKey(3);
                        
                    }

                }

                if (this->playGameVars.preventJumpDelay == 0 && PC::buttons.pressed(BTN_A) && (this->playGameVars.player.canMove(Movements::Jump) || this->playGameVars.player.canMove(Movements::JumpUp))) {

                    if (this->playGameVars.key.getKeyLocation() == KeyLocation::LowerPosition && this->playGameVars.player.getPosition() >= PLAYER_POS_LOWERKEY_START && this->playGameVars.player.getPosition() <= PLAYER_POS_LOWERKEY_END) {

                        this->playGameVars.key.setPath(Coordinates::LowerKey);

                        #ifdef INCLUDE_SOUND 
                            Utils::playSoundEffect(SoundEffects::ThrowKey);
                        #endif

                    }

                    if (this->playGameVars.key.getKeyLocation() == KeyLocation::UpperPosition && this->playGameVars.key.getPosition() == 0 && this->playGameVars.player.getPosition() >= PLAYER_POS_UPPERKEY_START && this->playGameVars.player.getPosition() <= PLAYER_POS_UPPERKEY_END) {

                        while (true) {

                            uint8_t r = random(0, 4);

                            if (!this->playGameVars.kong.getChain(r)) {
                                continue;
                            }

                            if (this->playGameVars.kong.getChain(r)) {
                                
                                if (this->cookie->viewSize == ViewSize::Normal) {
                                    this->playGameVars.key.setPath(Coordinates::Positions[r]);
                                }
                                else {
                                    this->playGameVars.key.setPath(Coordinates::Positions[r + 4]);
                                }
                        
                                #ifdef INCLUDE_SOUND 
                                    Utils::playSoundEffect(SoundEffects::ThrowKey);
                                #endif

                                break;

                            }

                        }

                    }

                    this->playGameVars.player.startJump();


                    if ((this->playGameVars.key.getKeyLocation() == KeyLocation::LowerPosition && this->playGameVars.player.getPosition() >= PLAYER_POS_LOWERKEY_START && this->playGameVars.player.getPosition() <= PLAYER_POS_LOWERKEY_END) ||
                        (this->playGameVars.key.getKeyLocation() == KeyLocation::UpperPosition && this->playGameVars.player.getPosition() >= PLAYER_POS_UPPERKEY_START && this->playGameVars.player.getPosition() <= PLAYER_POS_UPPERKEY_END)) {

                    }
                    else {

                        #ifdef INCLUDE_SOUND 
                            Utils::playSoundEffect(SoundEffects::Jump);
                        #endif                   

                    }

                }

            }

            // Player is jumping or falling ..

            else {

                if (this->playGameVars.player.isJumping()) {

                    this->playGameVars.player.updateJump();


                    // Have we jumped a clapper or a spark?

                    if (this->playGameVars.player.atTopOfJump()) {

                        uint16_t position = this->playGameVars.player.getPosition();
                        bool points = false;
printf("%i %i\n", position, PLAYER_CLAPPER_LOWER_START);
                        if (position >= PLAYER_CLAPPER_LOWER_START && position < PLAYER_CLAPPER_LOWER_END) {

                            for (uint8_t i = 0; i < CLAPPERS_LOWER_COUNT; i++) {

                                auto &clapper = this->playGameVars.lowerClappers.getClapper(i);

                                if (clapper.isEnabled() && abs(this->playGameVars.player.getXPosition(this->cookie->viewSize, false) - clapper.getXPosition(this->cookie->viewSize)) < JUMP_POINT_SPAN) {
                                    
                                    points = true;
                                    break;

                                } 

                            }

                        }

                        if (position >= PLAYER_SPARK_START && position < PLAYER_SPARK_END) {

                            for (uint8_t i = 0; i < SPARKS_LOWER_COUNT; i++) {

                                auto &spark = this->playGameVars.lowerSparks.getSpark(i);

                                if (spark.isEnabled() && abs(this->playGameVars.player.getXPosition(this->cookie->viewSize, false) - spark.getXPosition(this->cookie->viewSize)) < JUMP_POINT_SPAN) {

                                    points = true;
                                    break;

                                } 

                            }

                        }

                        if (position >= PLAYER_CLAPPER_UPPER_START && position < PLAYER_CLAPPER_UPPER_END) {

                            for (uint8_t i = 0; i < CLAPPERS_UPPER_COUNT; i++) {

                                auto &clapper = this->playGameVars.upperClappers.getClapper(i);

                                if (clapper.isEnabled() && abs(this->playGameVars.player.getXPosition(this->cookie->viewSize, false) - clapper.getXPosition(this->cookie->viewSize)) < JUMP_POINT_SPAN) {

                                    points = true;
                                    break;

                                } 

                            }

                        }

                        if (points) {

                            #ifdef INCLUDE_SOUND 
                                Utils::playSoundEffect(SoundEffects::JumpObstacle);
                            #endif

                            this->gameStats.score++;

                        }

                    }

                    if (this->playGameVars.player.isJumping() && this->playGameVars.player.canGrabChain()) {

                        switch (this->playGameVars.player.getPosition()) {

                            case PLAYER_VINE_0_MIN ... PLAYER_VINE_0:
                                this->playGameVars.player.setJumpPosition(0);
                                this->playGameVars.player.setPosition(this->cookie->viewSize, PLAYER_VINE_0_CLIMBING);
                                break;

                            case PLAYER_VINE_1_MIN ... PLAYER_VINE_1:
                                this->playGameVars.player.setJumpPosition(0);
                                this->playGameVars.player.setPosition(this->cookie->viewSize, PLAYER_VINE_1_CLIMBING);
                                break;

                            case PLAYER_CHAIN_0_GROUND_MIN ... PLAYER_CHAIN_0_GROUND_MAX - 1:
                                this->playGameVars.player.setJumpPosition(0);
                                this->playGameVars.player.setPosition(this->cookie->viewSize, PLAYER_CHAIN_0_CLIMBING);
                                break;

                            case PLAYER_CHAIN_1_GROUND_MIN ... PLAYER_CHAIN_1_GROUND_MAX - 1:
                                this->playGameVars.player.setJumpPosition(0);
                                this->playGameVars.player.setPosition(this->cookie->viewSize, PLAYER_CHAIN_1_CLIMBING);
                                break;

                            case PLAYER_CHAIN_2_GROUND_MIN ... PLAYER_CHAIN_2_GROUND_MAX - 1:
                                this->playGameVars.player.setJumpPosition(0);
                                this->playGameVars.player.setPosition(this->cookie->viewSize, PLAYER_CHAIN_2_CLIMBING);
                                break;

                            case PLAYER_CHAIN_3_GROUND_MIN ... PLAYER_CHAIN_3_GROUND_MAX - 1:
                                this->playGameVars.player.setJumpPosition(0);
                                this->playGameVars.player.setPosition(this->cookie->viewSize, PLAYER_CHAIN_3_CLIMBING);
                                break;
                                

                        }

                    }

                }

                if (!this->playGameVars.exitSequence && this->playGameVars.player.isFalling()) {
                    this->playGameVars.player.decPlayerPosition(this->cookie->viewSize, false);
                }

            }

        }

        uint8_t yOffset = this->playGameVars.player.getYOffset();


        // If we are in the middle of the exit sequence, move the player and kong automatically ..

        if (this->playGameVars.exitSequence) {

            if (this->playGameVars.kong.getPosition() == 50) {
                #ifdef INCLUDE_SOUND 
                Utils::playMusicStream(SoundEffects::FreeKong);
                #endif
            }

            if (this->playGameVars.playing) {


                this->playGameVars.key.updatePosition();
                this->playGameVars.kong.updateChains();

                uint16_t position = this->playGameVars.player.getPosition();

                switch (position) {

                    case PLAYER_CHAIN_0_BACKTOGROUND + 1 ... PLAYER_CHAIN_0_END:
                    case PLAYER_CHAIN_1_BACKTOGROUND + 1 ... PLAYER_CHAIN_1_END:
                    case PLAYER_CHAIN_2_BACKTOGROUND + 1 ... PLAYER_CHAIN_2_END:
                    case PLAYER_CHAIN_3_BACKTOGROUND + 1 ... PLAYER_CHAIN_3_END:
                        if (Utils::isFrameCount(2)) {
                            this->playGameVars.player.decPlayerPosition(this->cookie->viewSize, true);
                        }
                        break;

                    case PLAYER_CHAIN_MOVE_TO_EXIT_0 ... PLAYER_CHAIN_MOVE_TO_EXIT_END:
                        this->playGameVars.player.incPlayerPosition(this->cookie->viewSize);
                        break;

                }

                bool exitComplete = this->playGameVars.kong.updatePosition(this->cookie->viewSize);

                if (exitComplete) {

                    this->playGameVars.kong.reset();
                    this->playGameVars.player.setPosition(this->cookie->viewSize, 0);
                    this->playGameVars.exitSequence = false;
                    this->gameStats.score = this->gameStats.score + 20;

                    playGame_ScrollToBottom(false);

                }

            }

        }
        else {
                

            // Update entity positions ..

            if (this->playGameVars.playing) {

                bool updateChains = this->playGameVars.kong.updateChains();

                this->playGameVars.lowerClappers.updatePositions(this->cookie->viewSize);
                this->playGameVars.upperClappers.updatePositions(this->cookie->viewSize);
                this->playGameVars.key.updatePosition();
                this->playGameVars.birds.updatePositions();

                if (updateChains) {

                    this->playGameVars.player.setExit(true);
                    
                }

            }

            if (this->playGameVars.playing && Utils::getFrameCount(3) <= 1) {

                this->playGameVars.lowerSparks.updatePositions();

            }

            if (this->playGameVars.playing && Utils::isFrameCount(2)) {

                this->playGameVars.upperSparks.updatePositions();

            }

        }


        // Have we been hit by anything?

        #ifndef IGNORE_COLLISIONS
                
            Rect playerRect = this->playGameVars.player.getRect(this->cookie->viewSize);

            for (uint8_t i = 0; i < NUMBER_OF_ENTITIES; i++) {

                auto &lowerClapper = this->playGameVars.lowerClappers.getClapper(i);

                if (lowerClapper.isEnabled()) {

                    Rect clapperRect = lowerClapper.getRect(this->cookie->viewSize, yOffset, cookie->mode);

                    if (Utils::collide(playerRect, clapperRect)) {

                        playGame_KillPlayer();

                    }

                }

                auto &upperClapper = this->playGameVars.upperClappers.getClapper(i);

                if (upperClapper.isEnabled()) {

                    Rect clapperRect = upperClapper.getRect(this->cookie->viewSize, yOffset, cookie->mode);

                    if (Utils::collide(playerRect, clapperRect)) {

                        playGame_KillPlayer();
                        
                    }

                }


                if (this->playGameVars.player.getPosition() > PLAYER_SPARK_LOWER_IGNORE) {

                    auto &lowerSpark = this->playGameVars.lowerSparks.getSpark(i);

                    if (lowerSpark.isEnabled()) {

                        Rect sparkRect = lowerSpark.getRect(this->cookie->viewSize, yOffset, cookie->mode);

                        if (Utils::collide(playerRect, sparkRect)) {

                            playGame_KillPlayer();

                        }

                    }

                }

                auto &upperSpark = this->playGameVars.upperSparks.getSpark(i);

                if (upperSpark.isEnabled()) {

                    Rect sparkRect = upperSpark.getRect(this->cookie->viewSize, yOffset, cookie->mode);

                    if (Utils::collide(playerRect, sparkRect)) {

                        playGame_KillPlayer();

                    }

                }

                auto &bird = this->playGameVars.birds.getBird(i);

                if (bird.isEnabled()) {

                    Rect birdRect = bird.getRect(this->cookie->viewSize, yOffset, cookie->mode);

                    if (Utils::collide(playerRect, birdRect)) {

                        playGame_KillPlayer();
                        
                    }

                }

            }

        #endif

    }
    else if (this->playGame_GetPaused()) {

        // Handle pause menu ..

        if ((PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 1)) && this->playGameVars.pauseMenu == 0) {
            this->playGameVars.pauseMenu++;
        }

        if ((PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 1)) && this->playGameVars.pauseMenu == 1) {
             this->playGameVars.pauseMenu--;
        }                   

    }


    // End of Game?

    if (this->playGameVars.playing && this->gameStats.numberOfLivesLeft == 0) {

        this->gameStats.gameOver = true;
        this->playGameVars.playing = false;

        switch (this->cookie->mode) {

            case GameMode::Easy:
                if (this->gameStats.score > this->cookie->easyScore) {
                    this->cookie->easyScore = this->gameStats.score;
                    this->cookie->saveCookie();
                }
                break;

            case GameMode::Hard:
                if (this->gameStats.score > this->cookie->hardScore) {
                    this->cookie->hardScore = this->gameStats.score;
                    this->cookie->saveCookie();
                }
                break;

        }

        #ifdef INCLUDE_SOUND 
            Utils::playMusicStream(SoundEffects::GameOver);
        #endif

    }


    // Handle the transition to a new life ..

    switch (this->playGameVars.introDelay) {

        case INTRO_DELAY_FROM_TITLE_SCROLL:

            playGame_ScrollToBottom(true);

            if (this->playGameVars.clappersLowerDelay > CLAPPERS_LOWER_MIN) {

                this->playGameVars.clappersLowerDelay = this->playGameVars.clappersLowerDelay - CLAPPERS_LOWER_INC;
                this->playGameVars.lowerClappers.setDelayMax(this->playGameVars.clappersLowerDelay, true);

            }

            if (this->playGameVars.clappersUpperDelay > CLAPPERS_UPPER_MIN) {

                this->playGameVars.clappersUpperDelay = this->playGameVars.clappersUpperDelay - CLAPPERS_UPPER_INC;
                this->playGameVars.upperClappers.setDelayMax(this->playGameVars.clappersUpperDelay, true);

            }

            if (this->playGameVars.sparksLowerDelay > SPARKS_LOWER_MIN) {

                this->playGameVars.sparksLowerDelay = this->playGameVars.sparksLowerDelay - SPARKS_LOWER_INC;
                this->playGameVars.lowerSparks.setDelayMax(this->playGameVars.sparksLowerDelay, true);

            }

            if (this->playGameVars.sparksUpperDelay > SPARKS_UPPER_MIN) {

                this->playGameVars.sparksUpperDelay = this->playGameVars.sparksUpperDelay - SPARKS_UPPER_INC;
                this->playGameVars.upperSparks.setDelayMax(this->playGameVars.sparksUpperDelay, true);

            }

            if (this->playGameVars.birdsDelay > BIRDS_MIN) {

                this->playGameVars.birdsDelay = this->playGameVars.birdsDelay - BIRDS_INC;
                this->playGameVars.birds.setDelayMax(this->playGameVars.birdsDelay, true);

            }

            this->playGameVars.frameRate = this->playGameVars.frameRate + 2;
            PC::setFrameRate(this->playGameVars.frameRate);
            
            break;

        case 1:
            if (this->gameStats.numberOfLivesLeft > 0) {
                this->playGameVars.player.reset(this->cookie->viewSize);
                this->playGameVars.playing = true;
                this->gameStats.numberOfLivesLeft--;
            }
            break;

        default:
            break;

    }

    if (this->playGameVars.introDelay > 0) this->playGameVars.introDelay--;


    // Handle other buttons ..

    if (this->playGameVars.preventJumpDelay > 0) this->playGameVars.preventJumpDelay--;

    if (!this->playGameVars.playing && !this->gameStats.gameOver) {

        if (this->playGameVars.introDelay < 100 && (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B))) {

            this->playGameVars.playing = true;
            this->playGameVars.introDelay = 0;
            this->playGameVars.player.reset(this->cookie->viewSize);
            this->gameStats.numberOfLivesLeft--;

            if (PC::buttons.pressed(BTN_A)) {
                this->playGameVars.preventJumpDelay = 20;
            }

        }

    }
    else {    

        playGame_HandleCommonButtons();

    }

}


void Game::playGame_CheckLastKey(uint8_t chain) {

    #ifdef INCLUDE_SOUND 
    Utils::playSoundEffect(SoundEffects::Unlock);
    #endif
    
    this->playGameVars.kong.setFlashChain(chain, true);
    this->playGameVars.key.setFlash(true);

    this->gameStats.score = this->gameStats.score + random(8, 16);

    if (cookie->mode == GameMode::Easy) {

        this->playGameVars.upperClappers.reset(this->cookie->viewSize, 54);
        this->playGameVars.birds.reset();                            
        
    }

    for (uint8_t i = 0; i < 4 ; i++) {

        if (this->playGameVars.kong.getDisplayChain(i)) {

            // #ifdef INCLUDE_SOUND 
            // Utils::playSoundEffect(SoundEffects::Unlock);
            // #endif
            return;

        }

    }

    // #ifdef INCLUDE_SOUND 
    // Utils::playMusicStream(SoundEffects::FreeKong);
    // #endif

    this->playGameVars.lowerClappers.reset(this->cookie->viewSize, 107);
    this->playGameVars.upperClappers.reset(this->cookie->viewSize, 54);
    this->playGameVars.lowerSparks.reset(Coordinates::LowerSpark);
    this->playGameVars.upperSparks.reset(Coordinates::UpperSpark);
    this->playGameVars.birds.reset();
    this->playGameVars.exitSequence = true;

}

void Game::playGame_ScrollToBottom(bool renderKong) {

    playGame_DrawScenery(0);
    if (renderKong) playGame_RenderKong(0);
//    arduboy.displayWithBackground(Background::None);
//    delay(1000);

    for (uint8_t i = 0; i < 64 ; i++) {

        playGame_DrawScenery(i);
        playGame_RenderKey(i);
        playGame_RenderScore(i);
        if (renderKong) playGame_RenderKong(i);
//        arduboy.displayWithBackground(Background::None);
//        delay(20);
    
    }

}