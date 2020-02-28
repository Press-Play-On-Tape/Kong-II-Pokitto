#include "Game.h"
#include "Pokitto.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;


void Game::playGame_DrawScenery(uint8_t yOffset) {

    if (this->gameStats.viewSize == ViewSize::Normal) { 

        PD::drawBitmap(0, 0, Images_Normal::Scenery);

    }
    else {

        for (uint8_t i = 0; i < 16; i++) {

            PD::drawBitmap(0, (i * 16) - yOffset, Images_Large::Background[i]);

        }

    }

}

void Game::playGame_KillPlayer() {
    
    #ifdef PLAY_SOUNDS 
        sound.tones(Sounds::Death);
    #endif
    
    playGameVars.player.setDead(true);
    playGameVars.playing = false;
    playGameVars.introDelay = INTRO_DELAY_FROM_TITLE;
    playGameVars.key.setKeyLocation(KeyLocation::LowerPosition);

}

void Game::playGame_ResetLevel(uint8_t introDelay) {

    playGameVars.introDelay = introDelay;
    playGameVars.playing = false;

}

void Game::playGame_RenderScore(uint8_t yOffset) {

    if (this->gameStats.viewSize == ViewSize::Normal) { 

        if (gameStats.numberOfLivesLeft >= 3) {
            PD::drawBitmap(73, 144, Images_Normal::Jnr_Walking_L_F2);
        }

        if (gameStats.numberOfLivesLeft >= 2) {
            PD::drawBitmap(92, 144, Images_Normal::Jnr_Walking_L_F2);
        }

        PD::drawBitmap(127, 145, Images_Normal::Game_Icon[this->gameStats.mode == GameMode::Easy, 0, 1]);

        uint8_t digits[4] = {};
        Utils::extractDigits(digits, gameStats.score);

        for (uint8_t j = 4; j > 0; --j) {

            PD::drawBitmap(167 - (j*7), 146, Images_Normal::Numbers[digits[j - 1]]);

        }
        
    }
    else {

        if (gameStats.numberOfLivesLeft >= 3) {
            PD::drawBitmap(27, 118 - yOffset, Images_Normal::Jnr_Walking_L_F2);
        }

        if (gameStats.numberOfLivesLeft >= 2) {
            PD::drawBitmap(44, 118 - yOffset, Images_Normal::Jnr_Walking_L_F2);
        }

        PD::drawBitmap(81, 118, Images_Normal::Game_Icon[this->gameStats.mode == GameMode::Easy, 0, 1]);

        uint8_t digits[4] = {};
        Utils::extractDigits(digits, gameStats.score);

        for (uint8_t j = 4; j > 0; --j) {

            PD::drawBitmap(122 - (j*7), 120 - yOffset, Images_Normal::Numbers[digits[j - 1]]);

        }
    
    }

}


bool Game::playGame_GetPaused() {

  return playGameVars.paused;

}

void Game::playGame_SetPaused(bool value) {
  
  playGameVars.paused = value;

}

void Game::playGame_HandleCommonButtons() {

    if (gameStats.gameOver) {

        if (PC::buttons.pressed(BTN_A)) {
            gameState = GameStateType::HighScore_Activate; 
        }

    }
    else {

        if (PC::buttons.pressed(BTN_B)) {
            playGameVars.paused = !playGameVars.paused; 
        }

    }

}

void Game::playGame_RenderGameOverOrPause() {

    if (this->gameStats.viewSize == ViewSize::Normal) {

        // Game Over?

        if (gameStats.gameOver) {

            PD::drawBitmap(74, 68, Images_Normal::GameOver); 

        }

        // Pause?

        if (playGameVars.paused) {

            PD::drawBitmap(84, 68, Images_Normal::Pause); 

        }

    }
    else {

        // Game Over?

        if (gameStats.gameOver) {

            PD::drawBitmap(28, 13, Images_Normal::GameOver); 

        }

        // Pause?

        if (playGameVars.paused) {

            PD::drawBitmap(39, 16, Images_Normal::Pause); 

        }

    }

}
