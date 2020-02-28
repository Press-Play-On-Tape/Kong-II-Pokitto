#include "Game.h"
#include "Pokitto.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;



// ----------------------------------------------------------------------------
//  Render the state .. 
//
void Game::playGame_Render() {

    const uint8_t yOffset = playGameVars.player.getYOffset();
printf("%i\n", yOffset);


    // Draw Scenery ..

    playGame_DrawScenery(yOffset);


    // Draw player

    if (!gameStats.gameOver) {

        if (playGameVars.introDelay == 0) {

            uint8_t stance = playGameVars.player.getImage();
            uint8_t x = playGameVars.player.getXPosition(this->gameStats.viewSize, false);
            uint8_t y = playGameVars.player.getYPosition(this->gameStats.viewSize);

            if (this->gameStats.viewSize == ViewSize::Normal) {

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

            if ((playGameVars.introDelay / 20) % 2 == 0) {

                if (this->gameStats.viewSize == ViewSize::Normal) {

                    uint8_t x = playGameVars.player.getXPosition(this->gameStats.viewSize, false);
                    uint8_t y = playGameVars.player.getYPosition(this->gameStats.viewSize);

                    if (playGameVars.player.isDead()) {

                        uint8_t stance = playGameVars.player.getImage();
                        PD::drawBitmap(x, y, Images_Normal::Junior[stance]);

                    }
                    else {

                        PD::drawBitmap(x, y, Images_Normal::Jnr_Idle_R_F0);

                    }

                }
                else {

                    uint8_t x = playGameVars.player.getXPosition(this->gameStats.viewSize, false);
                    uint8_t y = playGameVars.player.getYPosition(this->gameStats.viewSize);

                    if (playGameVars.player.isDead()) {

                        uint8_t stance = playGameVars.player.getImage();
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

    if (playGameVars.kong.getEnabled()) {

        playGame_RenderKong(yOffset);

    }


    // Draw sparks / birds / clappers ..

    for (uint8_t i = 0; i < NUMBER_OF_ENTITIES; i++) {

        auto &lowerClapper = playGameVars.lowerClappers.getClapper(i);

        if (lowerClapper.isEnabled()) {

            int16_t x = lowerClapper.getXPosition(this->gameStats.viewSize);
            uint8_t y = lowerClapper.getYPosition(this->gameStats.viewSize, yOffset);
            uint8_t index = lowerClapper.getImage(this->gameStats.viewSize);

            PD::drawBitmap(x, y, Images_Normal::Clappers[index]);

        }

        auto &upperClapper = playGameVars.upperClappers.getClapper(i);

        if (upperClapper.isEnabled()) {

            int16_t x = upperClapper.getXPosition(this->gameStats.viewSize);
            uint8_t y = upperClapper.getYPosition(this->gameStats.viewSize, yOffset);
            uint8_t index = upperClapper.getImage(this->gameStats.viewSize);

            PD::drawBitmap(x, y, Images_Normal::Clappers[index]);

        }

        auto &lowerSpark = playGameVars.lowerSparks.getSpark(i);

        if (lowerSpark.isEnabled()) {

            uint8_t x = lowerSpark.getXPosition(this->gameStats.viewSize);
            uint8_t y = lowerSpark.getYPosition(this->gameStats.viewSize, yOffset);
            uint8_t index = lowerSpark.getImage();

            if (static_cast<SparkImage>(index) != SparkImage::None) {
                PD::drawBitmap(x, y, Images_Normal::Spark[index]);
            }

        }

        auto &upperSpark = playGameVars.upperSparks.getSpark(i);

        if (upperSpark.isEnabled()) {

            uint8_t x = upperSpark.getXPosition(this->gameStats.viewSize);
            uint8_t y = upperSpark.getYPosition(this->gameStats.viewSize, yOffset);
            uint8_t index = upperSpark.getImage();

            if (static_cast<SparkImage>(index) != SparkImage::None) {
                PD::drawBitmap(x, y, Images_Normal::Spark[index]);
            }

        }

        auto &bird = playGameVars.birds.getBird(i);

        if (bird.isEnabled()) {

            uint8_t x = bird.getXPosition(this->gameStats.viewSize);
            uint8_t y = bird.getYPosition(this->gameStats.viewSize, yOffset);
            uint8_t index = bird.getImage();

            if (static_cast<BirdImage>(index) != BirdImage::None) {

                PD::drawBitmap(x, y, Images_Normal::Birds[index]);

            }

        }

    }




    playGame_RenderKey(yOffset);
    playGame_RenderGameOverOrPause();


    // Render score ..

    playGame_RenderScore(yOffset);


    if (this->gameStats.viewSize == ViewSize::Normal) {

        PD::drawBitmap(VIEW_NORMAL_X_OFFSET - 8, 107 + VIEW_NORMAL_Y_LOWER_OFFSET, Images_Normal::Scenery_Edge_L);
        PD::drawBitmap(VIEW_NORMAL_X_OFFSET + 128, 107 + VIEW_NORMAL_Y_LOWER_OFFSET, Images_Normal::Scenery_Edge_R);
        PD::drawBitmap(VIEW_NORMAL_X_OFFSET - 8, 54 + VIEW_NORMAL_Y_UPPER_OFFSET, Images_Normal::Scenery_Edge_L);
        PD::drawBitmap(VIEW_NORMAL_X_OFFSET + 128, 54 + VIEW_NORMAL_Y_UPPER_OFFSET, Images_Normal::Scenery_Edge_R);
        PD::drawBitmap(VIEW_NORMAL_X_OFFSET + 128, 42 + VIEW_NORMAL_Y_UPPER_OFFSET, Images_Normal::Scenery_Edge_R_Large);
        PD::drawBitmap(55, 83, Images_Normal::Scenery_Middle);

    }

}


// ----------------------------------------------------------------------------
//  Render Kong .. 
//
void Game::playGame_RenderKong(uint8_t yOffset) {

    uint8_t x = playGameVars.kong.getXPosition(this->gameStats.viewSize);
    uint8_t y = playGameVars.kong.getYPosition(this->gameStats.viewSize, yOffset);
    KongImage image = playGameVars.kong.getImage();

    PD::drawBitmap(x, y, Images_Normal::Kong[static_cast<uint8_t>(image)]);
    
    if (this->gameStats.viewSize == ViewSize::Normal) {

        const uint8_t xPos[] = { 30 + VIEW_NORMAL_X_OFFSET, 47 + VIEW_NORMAL_X_OFFSET, 76 + VIEW_NORMAL_X_OFFSET, 83 + VIEW_NORMAL_X_OFFSET };
        const uint8_t yPos[] = { 6 + VIEW_NORMAL_Y_UPPER_OFFSET, 11 + VIEW_NORMAL_Y_UPPER_OFFSET, 11 + VIEW_NORMAL_Y_UPPER_OFFSET, 6 + VIEW_NORMAL_Y_UPPER_OFFSET };
        
        for (uint8_t i = 0; i < 4 ; i++) {

            if (playGameVars.kong.getDisplayChain(i)) {

                PD::drawBitmap(xPos[i], yPos[i], Images_Normal::Lock_Chains[i]);

            }

        }

    }
    else {

        const uint8_t xPos[] = { 30, 47, 76, 83 };
        const uint8_t yPos[] = { 6, 11, 11, 6 };
        
        for (uint8_t i = 0; i < 4 ; i++) {

            if (playGameVars.kong.getDisplayChain(i)) {

                PD::drawBitmap(xPos[i], yPos[i] - yOffset, Images_Normal::Lock_Chains[i]);

            }

        }

    }

}


// ----------------------------------------------------------------------------
//  Render key .. 
//
void Game::playGame_RenderKey(uint8_t yOffset) {

    // Render key ..

    if (playGameVars.key.getKeyLocation() != KeyLocation::None) {

        uint8_t x = playGameVars.key.getXPosition(this->gameStats.viewSize);
        uint8_t y = playGameVars.key.getYPosition(this->gameStats.viewSize, yOffset);
        uint8_t index = playGameVars.key.getImage();

        if (index == NO_IMAGE) {

            index = Utils::getFrameCount(59) / 15;
            PD::drawBitmap(x, y, Images_Normal::Key_Spin[index]);

        }
        else {

            if (playGameVars.key.getDisplay()) {
                PD::drawBitmap(x, y, Images_Normal::Key_Rotate[index]);
            }

        }

    }

}