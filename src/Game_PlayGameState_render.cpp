#include "Game.h"
#include "Pokitto.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;



// ----------------------------------------------------------------------------
//  Render the state .. 
//
void Game::playGame_Render() {

    const uint8_t yOffset = this->playGameVars.player.getYOffset();


    // Draw Scenery ..

    playGame_DrawScenery(yOffset);


    // Draw player

    if (!this->gameStats.gameOver) {

        if (this->playGameVars.introDelay == 0) {

            uint8_t stance = this->playGameVars.player.getImage();
            uint8_t x = this->playGameVars.player.getXPosition(this->cookie->viewSize, false);
            uint8_t y = this->playGameVars.player.getYPosition(this->cookie->viewSize);

            if (this->cookie->viewSize == ViewSize::Normal) {

                switch (y) {

                    case 70 ... 76:

                        switch (static_cast<Stance>(stance)) {

                            case Stance::Climbing_Vine_01:
                                PD::drawBitmap(x, y, Images_Normal::Jnr_Climbing_Vine_F0);
                                PD::drawBitmap(x, y + 15, Images_Normal::Jnr_Climbing_Vine_F0_BottomHalf);
                                break;

                            case Stance::Climbing_Vine_02:
                                PD::drawBitmap(x, y, Images_Normal::Jnr_Climbing_Vine_F1);
                                PD::drawBitmap(x, y + 15, Images_Normal::Jnr_Climbing_Vine_F1_BottomHalf);
                                break;

                        }

                        break;

                    case 77 ... 81:

                        switch (static_cast<Stance>(stance)) {

                            case Stance::Climbing_Vine_01:
                                PD::drawBitmap(x, y, Images_Normal::Jnr_Climbing_Vine_F0_TopHalf);
                                PD::drawBitmap(x, y + 8, Images_Normal::Jnr_Climbing_Vine_F0);
                                break;

                            case Stance::Climbing_Vine_02:
                                PD::drawBitmap(x, y, Images_Normal::Jnr_Climbing_Vine_F1_TopHalf);
                                PD::drawBitmap(x, y + 8, Images_Normal::Jnr_Climbing_Vine_F1);
                                break;

                        }

                        break;

                    default:
                        PD::drawBitmap(x, y, Images_Normal::Junior[stance]);
                        break;

                }

            }
            else {
    
                PD::drawBitmap(x, y, Images_Large::Junior[stance]);

            }

        }
        else {

            if ((this->playGameVars.introDelay / 20) % 2 == 0) {

                if (this->cookie->viewSize == ViewSize::Normal) {

                    uint8_t x = this->playGameVars.player.getXPosition(this->cookie->viewSize, false);
                    uint8_t y = this->playGameVars.player.getYPosition(this->cookie->viewSize);

                    if (this->playGameVars.player.isDead()) {

                        uint8_t stance = this->playGameVars.player.getImage();
                        PD::drawBitmap(x, y, Images_Normal::Junior[stance]);

                    }
                    else {

                        PD::drawBitmap(x, y, Images_Normal::Jnr_Idle_R_F0);

                    }

                }
                else {

                    uint8_t x = this->playGameVars.player.getXPosition(this->cookie->viewSize, false);
                    uint8_t y = this->playGameVars.player.getYPosition(this->cookie->viewSize);

                    if (this->playGameVars.player.isDead()) {

                        uint8_t stance = this->playGameVars.player.getImage();
                        PD::drawBitmap(x, y, Images_Large::Junior[stance]);

                    }
                    else {

                        PD::drawBitmap(x, y, Images_Large::Jnr_Idle_R_F0);

                    }
                    
                }

            }

        }

    }

    // Draw Kong

    if (this->playGameVars.kong.getEnabled()) {

        playGame_RenderKong(yOffset);

    }


    // Draw sparks / birds / clappers ..

    for (uint8_t i = 0; i < NUMBER_OF_ENTITIES; i++) {

        auto &lowerClapper = this->playGameVars.lowerClappers.getClapper(i);

        if (lowerClapper.isEnabled()) {

            int16_t x = lowerClapper.getXPosition(this->cookie->viewSize);
            uint8_t y = lowerClapper.getYPosition(this->cookie->viewSize, yOffset);
            uint8_t index = lowerClapper.getImage(this->cookie->viewSize);

            if (this->cookie->viewSize == ViewSize::Normal) {
                PD::drawBitmap(x, y, Images_Normal::Clappers[index]);
            }
            else {
                PD::drawBitmap(x, y, Images_Large::Clappers[index]);    
            }

        }

        auto &upperClapper = this->playGameVars.upperClappers.getClapper(i);

        if (upperClapper.isEnabled()) {

            int16_t x = upperClapper.getXPosition(this->cookie->viewSize);
            uint8_t y = upperClapper.getYPosition(this->cookie->viewSize, yOffset);
            uint8_t index = upperClapper.getImage(this->cookie->viewSize);

            if (this->cookie->viewSize == ViewSize::Normal) {
                PD::drawBitmap(x, y, Images_Normal::Clappers[index]);
            }
            else {
                PD::drawBitmap(x, y, Images_Large::Clappers[index]);    
            }

        }

        auto &lowerSpark = this->playGameVars.lowerSparks.getSpark(i);

        if (lowerSpark.isEnabled()) {

            uint8_t x = lowerSpark.getXPosition(this->cookie->viewSize);
            uint8_t y = lowerSpark.getYPosition(this->cookie->viewSize, yOffset);
            uint8_t index = lowerSpark.getImage();

            if (static_cast<SparkImage>(index) != SparkImage::None) {

                if (this->cookie->viewSize == ViewSize::Normal) {
                    PD::drawBitmap(x, y, Images_Normal::Spark[index]);
                }
                else {
                    PD::drawBitmap(x, y, Images_Large::Spark[index]);    
                }

            }

        }

        auto &upperSpark = this->playGameVars.upperSparks.getSpark(i);

        if (upperSpark.isEnabled()) {

            uint8_t x = upperSpark.getXPosition(this->cookie->viewSize);
            uint8_t y = upperSpark.getYPosition(this->cookie->viewSize, yOffset);
            uint8_t index = upperSpark.getImage();

            if (static_cast<SparkImage>(index) != SparkImage::None) {

                if (this->cookie->viewSize == ViewSize::Normal) {
                    PD::drawBitmap(x, y, Images_Normal::Spark[index]);
                }
                else {
                    PD::drawBitmap(x, y, Images_Large::Spark[index]);    
                }

            }

        }

        auto &bird = this->playGameVars.birds.getBird(i);

        if (bird.isEnabled()) {

            uint8_t x = bird.getXPosition(this->cookie->viewSize);
            uint8_t y = bird.getYPosition(this->cookie->viewSize, yOffset);
            uint8_t index = bird.getImage();

            if (static_cast<BirdImage>(index) != BirdImage::None) {

                if (this->cookie->viewSize == ViewSize::Normal) {
                    PD::drawBitmap(x, y, Images_Normal::Birds[index]);
                }
                else {
                    PD::drawBitmap(x, y, Images_Large::Birds[index]);    
                }

            }

        }

    }


    this->playGame_RenderKey(yOffset);



    // Render score ..

    this->playGame_RenderScore(yOffset);


    if (this->cookie->viewSize == ViewSize::Normal) {

        PD::drawBitmap(VIEW_NORMAL_X_OFFSET - 8, 107 + VIEW_NORMAL_Y_LOWER_OFFSET, Images_Normal::Scenery_Edge_L);
        PD::drawBitmap(VIEW_NORMAL_X_OFFSET + 128, 107 + VIEW_NORMAL_Y_LOWER_OFFSET, Images_Normal::Scenery_Edge_R);
        PD::drawBitmap(VIEW_NORMAL_X_OFFSET - 8, 54 + VIEW_NORMAL_Y_UPPER_OFFSET, Images_Normal::Scenery_Edge_L);
        PD::drawBitmap(VIEW_NORMAL_X_OFFSET + 128, 54 + VIEW_NORMAL_Y_UPPER_OFFSET, Images_Normal::Scenery_Edge_R);
        PD::drawBitmap(VIEW_NORMAL_X_OFFSET + 128, 42 + VIEW_NORMAL_Y_UPPER_OFFSET, Images_Normal::Scenery_Edge_R_Large);
        PD::drawBitmap(55, 83, Images_Normal::Scenery_Middle);

    }

    this->playGame_RenderGameOverOrPause();

}


// ----------------------------------------------------------------------------
//  Render Kong .. 
//
void Game::playGame_RenderKong(uint8_t yOffset) {

    uint8_t x = this->playGameVars.kong.getXPosition(this->cookie->viewSize);
    int8_t y = this->playGameVars.kong.getYPosition(this->cookie->viewSize, yOffset);
    KongImage image = this->playGameVars.kong.getImage();

    if (this->cookie->viewSize == ViewSize::Normal) {
        PD::drawBitmap(x, y, Images_Normal::Kong[static_cast<uint8_t>(image)]);
    }
    else {
        PD::drawBitmap(x, y, Images_Large::Kong[static_cast<uint8_t>(image)]);
    }
    
    if (this->cookie->viewSize == ViewSize::Normal) {

        const uint8_t xPos[] = { 30 + VIEW_NORMAL_X_OFFSET, 47 + VIEW_NORMAL_X_OFFSET, 76 + VIEW_NORMAL_X_OFFSET, 83 + VIEW_NORMAL_X_OFFSET };
        const uint8_t yPos[] = { 6 + VIEW_NORMAL_Y_UPPER_OFFSET, 11 + VIEW_NORMAL_Y_UPPER_OFFSET, 11 + VIEW_NORMAL_Y_UPPER_OFFSET, 6 + VIEW_NORMAL_Y_UPPER_OFFSET };
        
        for (uint8_t i = 0; i < 4 ; i++) {

            if (this->playGameVars.kong.getDisplayChain(i)) {

                PD::drawBitmap(xPos[i], yPos[i], Images_Normal::Lock_Chains[i]);

            }

        }

    }
    else {

        const uint8_t xPos[] = { 46, 81, 138, 153 };
        const uint8_t yPos[] = { 12, 22, 22, 12 };
        
        for (uint8_t i = 0; i < 4 ; i++) {

            if (this->playGameVars.kong.getDisplayChain(i)) {

                PD::drawBitmap(xPos[i], yPos[i] - yOffset, Images_Large::Lock_Chains[i]);

            }

        }

    }

}


// ----------------------------------------------------------------------------
//  Render key .. 
//
void Game::playGame_RenderKey(uint8_t yOffset) {

    // Render key ..

    if (this->playGameVars.key.getKeyLocation() != KeyLocation::None) {

        uint8_t x = this->playGameVars.key.getXPosition(this->cookie->viewSize);
        int16_t y = this->playGameVars.key.getYPosition(this->cookie->viewSize, yOffset);
        uint8_t index = this->playGameVars.key.getImage();

        if (this->cookie->viewSize == ViewSize::Normal) {

            if (index == NO_IMAGE) {
                
                index = Utils::getFrameCount(59) / 15;
                PD::drawBitmap(x, y, Images_Normal::Key_Spin[index]);

            }
            else {

                if (this->playGameVars.key.getDisplay()) {
                    PD::drawBitmap(x, y, Images_Normal::Key_Rotate[index]);
                }

            }

        }
        else {

            if (index == NO_IMAGE) {
                
                index = Utils::getFrameCount(59) / 15;
                PD::drawBitmap(x, y, Images_Large::Key_Spin[index]);

            }
            else {

                if (this->playGameVars.key.getDisplay()) {
                    PD::drawBitmap(x, y, Images_Large::Key_Rotate[index]);
                }

            }

        }

    }

}