#include "Game.h"
#include "Pokitto.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;


void Game::playGame_DrawScenery(uint8_t yOffset) {

    if (this->cookie->viewSize == ViewSize::Normal) { 

        PD::drawBitmap(0, 0, Images_Normal::Scenery);

    }
    else {

        for (uint8_t i = 0; i < 16; i++) {

            PD::drawBitmap(0, (i * 16) - yOffset, Images_Large::Background[i]);

        }

    }

}

void Game::playGame_KillPlayer() {
    
    #ifdef INCLUDE_SOUND 
        Utils::playSoundEffect(SoundEffects::Collide);
    #endif
    
    this->playGameVars.player.setDead(true);
    this->playGameVars.playing = false;
    this->playGameVars.introDelay = INTRO_DELAY_FROM_TITLE;
    this->playGameVars.key.setKeyLocation(KeyLocation::LowerPosition);

}

void Game::playGame_ResetLevel(uint8_t introDelay) {

    this->playGameVars.introDelay = introDelay;
    this->playGameVars.playing = false;

}

void Game::playGame_RenderScore(uint8_t yOffset) {

    if (this->cookie->viewSize == ViewSize::Normal) { 

        if (this->gameStats.numberOfLivesLeft >= 3) {
            PD::drawBitmap(73, 144, Images_Normal::Jnr_Walking_L_F2);
        }

        if (this->gameStats.numberOfLivesLeft >= 2) {
            PD::drawBitmap(92, 144, Images_Normal::Jnr_Walking_L_F2);
        }

        switch (this->cookie->mode) {

            case GameMode::Easy:
                PD::drawBitmap(127, 145, Images_Normal::GameA);
                break;

            case GameMode::Hard:
                PD::drawBitmap(127, 145, Images_Normal::GameB);
                break;

            case GameMode::Tux:
                PD::drawBitmap(127, 145, Images_Normal::GameC);
                break;

        }

        uint8_t digits[4] = {};
        Utils::extractDigits(digits, this->gameStats.score);

        for (uint8_t j = 4; j > 0; --j) {

            PD::drawBitmap(167 - (j*7), 146, Images_Normal::Numbers[digits[j - 1]]);

        }
        
    }
    else {

        if (this->gameStats.numberOfLivesLeft >= 3) {
            PD::drawBitmap(47, 235 - yOffset, Images_Large::Jnr_Walking_L_F2);
        }

        if (this->gameStats.numberOfLivesLeft >= 2) {
            PD::drawBitmap(85, 235 - yOffset, Images_Large::Jnr_Walking_L_F2);
        }

        switch (this->cookie->mode) {

            case GameMode::Easy:
                PD::drawBitmap(135, 235 - yOffset, Images_Large::GameA);
                break;

            case GameMode::Hard:
                PD::drawBitmap(135, 235 - yOffset, Images_Large::GameB);
                break;

            case GameMode::Tux:
                PD::drawBitmap(135, 235 - yOffset, Images_Large::GameC);
                break;

        }

        uint8_t digits[4] = {};
        Utils::extractDigits(digits, this->gameStats.score);

        for (uint8_t j = 4; j > 0; --j) {

            PD::drawBitmap(217 - (j*14), 238 - yOffset, Images_Large::Numbers[digits[j - 1]]);

        }
    
    }

}


bool Game::playGame_GetPaused() {

  return this->playGameVars.paused;

}

void Game::playGame_SetPaused(bool value) {
  
  this->playGameVars.paused = value;

}

void Game::playGame_HandleCommonButtons() {

    if (this->gameStats.gameOver) {

        if (PC::buttons.pressed(BTN_A)) {
            gameState = GameStateType::TitleScreen_Activate; 
        }

    }
    else {

        if (this->playGameVars.paused) {

            if (this->playGameVars.pauseMenu == 0 && (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_C))) {
                this->playGameVars.paused = false;
            }

            if (this->playGameVars.pauseMenu == 1 && PC::buttons.pressed(BTN_A)) {
                gameState = GameStateType::TitleScreen_Activate; 
            }

        }
        else {

            if (PC::buttons.pressed(BTN_C)) {
                this->playGameVars.paused = true; 
            }

        }

    }

}

void Game::playGame_RenderGameOverOrPause() {

    // Game Over?

    if (this->gameStats.gameOver) {

        if (this->cookie->viewSize == ViewSize::Normal) {
            PD::drawBitmap(26, 63, Images_Normal::GameOver); 
        }
        else {
            PD::drawBitmap(24, 18, Images_Large::GameOver); 
        }

    }

    // Pause?

    if (this->playGameVars.paused) {

        PD::drawBitmap(29, 64, Images_Normal::Pause); 

        if (this->playGameVars.pauseMenu == 0) { PD::drawBitmap(40, 76, Images_Normal::Selector); }
        if (this->playGameVars.pauseMenu == 1) { PD::drawBitmap(40, 90, Images_Normal::Selector); }

    }

}
