#include "Game.h"
#include "Pokitto.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;



// ----------------------------------------------------------------------------
//    Handle state updates .. 
//
void Game::playGame_Update() { 

    if (!playGame_GetPaused() && !playGameVars.player.isDead()) {


        // Handle player movements ..

//        if (playGameVars.playing && Utils::isFrameCount(2)) {
        if (playGameVars.playing) {

            playGameVars.player.getXPosition(this->gameStats.viewSize, true);

            if (!playGameVars.player.isJumping() && !playGameVars.player.isFalling() && !playGameVars.exitSequence) {


                // If the player is running from right to left, the controls are reversed ..

                if (playGameVars.player.canMove(Movements::Reverse)) {

                    if ((PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 1)) && playGameVars.player.canMove(Movements::Left)) {
                        playGameVars.player.incPlayerPosition();
                    }

                    if ((PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1)) && playGameVars.player.canMove(Movements::Right)) {
                        playGameVars.player.decPlayerPosition(false);
                    }

                }
                else {

                    if ((PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1)) && playGameVars.player.canMove(Movements::Right)) {
                        playGameVars.player.incPlayerPosition();
                    }

                    if ((PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 1)) && playGameVars.player.canMove(Movements::Left)) {
                        playGameVars.player.decPlayerPosition(false);
                    }

                }

                if ((PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 1)) && playGameVars.player.canMove(Movements::Down)) {
                    playGameVars.player.decPlayerPosition(false);
                }

                if ((PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 1)) && playGameVars.player.canMove(Movements::Up)) {
                    
                    playGameVars.player.incPlayerPosition();

                    if (playGameVars.player.getPosition() == PLAYER_CHAIN_0_END - 1 && playGameVars.key.getKeyLocation() == KeyLocation::Position_00 && !playGameVars.kong.getFlashChain(0)) {

                        playGame_CheckLastKey(0);
                        
                    }
                    else if (playGameVars.player.getPosition() == PLAYER_CHAIN_1_END - 1 && playGameVars.key.getKeyLocation() == KeyLocation::Position_01 && !playGameVars.kong.getFlashChain(1)) {

                        playGame_CheckLastKey(1);
                        
                    }
                    else if (playGameVars.player.getPosition() == PLAYER_CHAIN_2_END - 1 && playGameVars.key.getKeyLocation() == KeyLocation::Position_02 && !playGameVars.kong.getFlashChain(2)) {

                        playGame_CheckLastKey(2);
                        
                    }
                    else if (playGameVars.player.getPosition() == PLAYER_CHAIN_3_END - 1 && playGameVars.key.getKeyLocation() == KeyLocation::Position_03 && !playGameVars.kong.getFlashChain(3)) {

                        playGame_CheckLastKey(3);
                        
                    }

                }

                if (playGameVars.preventJumpDelay == 0 && PC::buttons.pressed(BTN_A) && (playGameVars.player.canMove(Movements::Jump) || playGameVars.player.canMove(Movements::JumpUp))) {

                    if (playGameVars.key.getKeyLocation() == KeyLocation::LowerPosition && playGameVars.player.getPosition() >= PLAYER_POS_LOWERKEY_START && playGameVars.player.getPosition() <= PLAYER_POS_LOWERKEY_END) {

                        playGameVars.key.setPath(Coordinates::LowerKey);

                        #ifdef PLAY_SOUNDS 
                            sound.tones(Sounds::Key);
                        #endif

                    }

                    if (playGameVars.key.getKeyLocation() == KeyLocation::UpperPosition && playGameVars.player.getPosition() >= PLAYER_POS_UPPERKEY_START && playGameVars.player.getPosition() <= PLAYER_POS_UPPERKEY_END) {

                        while (true) {

                            uint8_t r = random(0, 4);

                            if (!playGameVars.kong.getChain(r)) {
                                continue;
                            }

                            if (playGameVars.kong.getChain(r)) {
                                
                                //playGameVars.key.setPath(pgm_read_word_near(&Coordinates::Positions[r]));
                        
                                #ifdef PLAY_SOUNDS 
                                    sound.tones(Sounds::Key);
                                #endif

                                break;

                            }

                        }

                    }

                    playGameVars.player.startJump();

                    #ifdef PLAY_SOUNDS 
                        sound.tones(Sounds::Jump);
                    #endif                   

                }

            }

            // Player is jumping or falling ..

            else {

                if (playGameVars.player.isJumping()) {

                    playGameVars.player.updateJump();


                    // Have we jumped a clapper or a spark?

                    if (playGameVars.player.atTopOfJump()) {

                        uint16_t position = playGameVars.player.getPosition();
                        bool points = false;

                        if (position >= PLAYER_CLAPPER_LOWER_START && position < PLAYER_CLAPPER_LOWER_END) {

                            for (uint8_t i = 0; i < CLAPPERS_LOWER_COUNT; i++) {

                                auto &clapper = playGameVars.lowerClappers.getClapper(i);

                                if (clapper.isEnabled() && abs(playGameVars.player.getXPosition(this->gameStats.viewSize, false) - clapper.getXPosition(this->gameStats.viewSize)) < JUMP_POINT_SPAN) {

                                    points = true;
                                    break;

                                } 

                            }

                        }

                        if (position >= PLAYER_SPARK_START && position < PLAYER_SPARK_END) {

                            for (uint8_t i = 0; i < SPARKS_LOWER_COUNT; i++) {

                                auto &spark = playGameVars.lowerSparks.getSpark(i);

                                if (spark.isEnabled() && abs(playGameVars.player.getXPosition(this->gameStats.viewSize, false) - spark.getXPosition(this->gameStats.viewSize)) < JUMP_POINT_SPAN) {

                                    points = true;
                                    break;

                                } 

                            }

                        }

                        if (position >= PLAYER_CLAPPER_UPPER_START && position < PLAYER_CLAPPER_UPPER_END) {

                            for (uint8_t i = 0; i < CLAPPERS_UPPER_COUNT; i++) {

                                auto &clapper = playGameVars.upperClappers.getClapper(i);

                                if (clapper.isEnabled() && abs(playGameVars.player.getXPosition(this->gameStats.viewSize, false) - clapper.getXPosition(this->gameStats.viewSize)) < JUMP_POINT_SPAN) {

                                    points = true;
                                    break;

                                } 

                            }

                        }

                        if (points) {

                            #ifdef PLAY_SOUNDS 
                                sound.tones(Sounds::JumpOver);
                            #endif

                            gameStats.score++;

                        }

                    }

                    if (playGameVars.player.isJumping() && playGameVars.player.canGrabChain()) {

                        switch (playGameVars.player.getPosition()) {

                            case PLAYER_VINE_0_MIN ... PLAYER_VINE_0:
                                playGameVars.player.setJumpPosition(0);
                                playGameVars.player.setPosition(PLAYER_VINE_0_CLIMBING);
                                break;

                            case PLAYER_VINE_1_MIN ... PLAYER_VINE_1:
                                playGameVars.player.setJumpPosition(0);
                                playGameVars.player.setPosition(PLAYER_VINE_1_CLIMBING);
                                break;

                            case PLAYER_CHAIN_0_GROUND_MIN ... PLAYER_CHAIN_0_GROUND_MAX - 1:
                                playGameVars.player.setJumpPosition(0);
                                playGameVars.player.setPosition(PLAYER_CHAIN_0_CLIMBING);
                                break;

                            case PLAYER_CHAIN_1_GROUND_MIN ... PLAYER_CHAIN_1_GROUND_MAX - 1:
                                playGameVars.player.setJumpPosition(0);
                                playGameVars.player.setPosition(PLAYER_CHAIN_1_CLIMBING);
                                break;

                            case PLAYER_CHAIN_2_GROUND_MIN ... PLAYER_CHAIN_2_GROUND_MAX - 1:
                                playGameVars.player.setJumpPosition(0);
                                playGameVars.player.setPosition(PLAYER_CHAIN_2_CLIMBING);
                                break;

                            case PLAYER_CHAIN_3_GROUND_MIN ... PLAYER_CHAIN_3_GROUND_MAX - 1:
                                playGameVars.player.setJumpPosition(0);
                                playGameVars.player.setPosition(PLAYER_CHAIN_3_CLIMBING);
                                break;
                                

                        }

                    }

                }

                if (!playGameVars.exitSequence && playGameVars.player.isFalling()) {
                    playGameVars.player.decPlayerPosition(false);
                }

            }

        }

        uint8_t yOffset = playGameVars.player.getYOffset();


        // If we are in the middle of the exit sequence, move the player and kong automatically ..

        if (playGameVars.exitSequence) {

//            if (playGameVars.playing && Utils::isFrameCount(2)) {
            if (playGameVars.playing) {

                playGameVars.key.updatePosition();
                playGameVars.kong.updateChains();

                uint16_t position = playGameVars.player.getPosition();

                switch (position) {

                    case PLAYER_CHAIN_0_BACKTOGROUND + 1 ... PLAYER_CHAIN_0_END:
                    case PLAYER_CHAIN_1_BACKTOGROUND + 1 ... PLAYER_CHAIN_1_END:
                    case PLAYER_CHAIN_2_BACKTOGROUND + 1 ... PLAYER_CHAIN_2_END:
                    case PLAYER_CHAIN_3_BACKTOGROUND + 1 ... PLAYER_CHAIN_3_END:
//                        if (Utils::isFrameCount(3)) {
                        if (Utils::isFrameCount(2)) {
                            playGameVars.player.decPlayerPosition(true);
                        }
                        break;

                    case PLAYER_CHAIN_MOVE_TO_EXIT_0 ... PLAYER_CHAIN_MOVE_TO_EXIT_END:
//                        if (Utils::isFrameCount(2)) {
                            playGameVars.player.incPlayerPosition();
//                        }
                        break;

                }

                bool exitComplete = playGameVars.kong.updatePosition();

                if (exitComplete) {

                    playGameVars.kong.reset();
                    playGameVars.player.setPosition(0);
                    playGameVars.exitSequence = false;

                    playGame_ScrollToBottom(false);

                }

            }

        }
        else {
                

            // Update entity positions ..

//            if (playGameVars.playing && Utils::isFrameCount(2)) {
            if (playGameVars.playing) {

                bool updateChains = playGameVars.kong.updateChains();

                playGameVars.lowerClappers.updatePositions();
                playGameVars.upperClappers.updatePositions();
                playGameVars.key.updatePosition();
                playGameVars.birds.updatePositions();

                if (updateChains) {

                    playGameVars.player.setExit(true);
                    
                }

            }

//            if (playGameVars.playing && Utils::isFrameCount(3)) {
            if (playGameVars.playing && Utils::isFrameCount(2)) {

                playGameVars.lowerSparks.updatePositions();

            }

//            if (playGameVars.playing && Utils::isFrameCount(4)) {
            if (playGameVars.playing && Utils::isFrameCount(2)) {

                playGameVars.upperSparks.updatePositions();

            }

        }


        // Have we been hit by anything?

        #ifndef IGNORE_COLLISIONS
                
            Rect playerRect = playGameVars.player.getRect();

            for (uint8_t i = 0; i < NUMBER_OF_ENTITIES; i++) {

                auto &lowerClapper = playGameVars.lowerClappers.getClapper(i);

                if (lowerClapper.isEnabled()) {

                    Rect clapperRect = lowerClapper.getRect(yOffset, gameStats.mode);

                    if (Utils::collide(playerRect, clapperRect)) {

                        playGame_KillPlayer();

                    }

                }

                auto &upperClapper = playGameVars.upperClappers.getClapper(i);

                if (upperClapper.isEnabled()) {

                    Rect clapperRect = upperClapper.getRect(yOffset, gameStats.mode);

                    if (Utils::collide(playerRect, clapperRect)) {

                        playGame_KillPlayer();
                        
                    }

                }


                if (playGameVars.player.getPosition() > PLAYER_SPARK_LOWER_IGNORE) {

                    auto &lowerSpark = playGameVars.lowerSparks.getSpark(i);

                    if (lowerSpark.isEnabled()) {

                        Rect sparkRect = lowerSpark.getRect(yOffset, gameStats.mode);

                        if (Utils::collide(playerRect, sparkRect)) {

                            playGame_KillPlayer();

                        }

                    }

                }

                auto &upperSpark = playGameVars.upperSparks.getSpark(i);

                if (upperSpark.isEnabled()) {

                    Rect sparkRect = upperSpark.getRect(yOffset, gameStats.mode);

                    if (Utils::collide(playerRect, sparkRect)) {

                        playGame_KillPlayer();

                    }

                }

                auto &bird = playGameVars.birds.getBird(i);

                if (bird.isEnabled()) {

                    Rect birdRect = bird.getRect(yOffset, gameStats.mode);

                    if (Utils::collide(playerRect, birdRect)) {

                        playGame_KillPlayer();
                        
                    }

                }

            }

        #endif

    }


    // End of Game?

    if (playGameVars.playing && gameStats.numberOfLivesLeft == 0) {

        gameStats.gameOver = true;
        playGameVars.playing = false;

        #ifdef PLAY_SOUNDS 
            sound.tones(Sounds::GameOver);
        #endif

    }


    // Handle the transition to a new life ..

    switch (playGameVars.introDelay) {

        case INTRO_DELAY_FROM_TITLE_SCROLL:

            playGame_ScrollToBottom(true);

            if (playGameVars.clappersLowerDelay > CLAPPERS_LOWER_MIN) {

                playGameVars.clappersLowerDelay = playGameVars.clappersLowerDelay - CLAPPERS_LOWER_INC;
                playGameVars.lowerClappers.setDelayMax(playGameVars.clappersLowerDelay, true);

            }

            if (playGameVars.clappersUpperDelay > CLAPPERS_UPPER_MIN) {

                playGameVars.clappersUpperDelay = playGameVars.clappersUpperDelay - CLAPPERS_UPPER_INC;
                playGameVars.upperClappers.setDelayMax(playGameVars.clappersUpperDelay, true);

            }

            if (playGameVars.sparksLowerDelay > SPARKS_LOWER_MIN) {

                playGameVars.sparksLowerDelay = playGameVars.sparksLowerDelay - SPARKS_LOWER_INC;
                playGameVars.lowerSparks.setDelayMax(playGameVars.sparksLowerDelay, true);

            }

            if (playGameVars.sparksUpperDelay > SPARKS_UPPER_MIN) {

                playGameVars.sparksUpperDelay = playGameVars.sparksUpperDelay - SPARKS_UPPER_INC;
                playGameVars.upperSparks.setDelayMax(playGameVars.sparksUpperDelay, true);

            }

            if (playGameVars.birdsDelay > BIRDS_MIN) {

                playGameVars.birdsDelay = playGameVars.birdsDelay - BIRDS_INC;
                playGameVars.birds.setDelayMax(playGameVars.birdsDelay, true);

            }

            playGameVars.frameRate = playGameVars.frameRate + 2;
            PC::setFrameRate(playGameVars.frameRate);
            
            break;

        case 1:
            if (gameStats.numberOfLivesLeft > 0) {
                playGameVars.player.reset();
                playGameVars.playing = true;
                gameStats.numberOfLivesLeft--;
            }
            break;

        default:
            break;

    }

    if (playGameVars.introDelay > 0) playGameVars.introDelay--;


    // Handle other buttons ..

    if (playGameVars.preventJumpDelay > 0) playGameVars.preventJumpDelay--;

    if (!playGameVars.playing && !gameStats.gameOver) {

        if (playGameVars.introDelay < 100 && (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B))) {

            playGameVars.playing = true;
            playGameVars.introDelay = 0;
            playGameVars.player.reset();
            gameStats.numberOfLivesLeft--;

            if (PC::buttons.pressed(BTN_A)) {
                playGameVars.preventJumpDelay = 20;
            }

        }

    }
    else {    

        playGame_HandleCommonButtons();

    }

}


void Game::playGame_CheckLastKey(uint8_t chain) {

    playGameVars.kong.setFlashChain(chain, true);
    playGameVars.key.setFlash(true);

    gameStats.score = gameStats.score + random(8, 16);

    if (gameStats.mode == GameMode::Easy) {

        playGameVars.upperClappers.reset(54);
        playGameVars.birds.reset();                            
        
    }

    #ifdef PLAY_SOUNDS 
        sound.tones(Sounds::Unlock);
    #endif

    for (uint8_t i = 0; i < 4 ; i++) {

        if (playGameVars.kong.getDisplayChain(i)) return;

    }

    playGameVars.lowerClappers.reset(107);
    playGameVars.upperClappers.reset(54);
    playGameVars.lowerSparks.reset(Coordinates::LowerSpark);
    playGameVars.upperSparks.reset(Coordinates::UpperSpark);
    playGameVars.birds.reset();
    playGameVars.exitSequence = true;

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