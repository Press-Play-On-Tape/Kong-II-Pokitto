#include "Game.h"
#include "Pokitto.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;


void Game::playGame_DrawScenery(uint8_t yOffset) {

    if (this->gameStats.viewSize == ViewSize::Normal) { 
        PD::drawBitmap(0, 0, Images::Scenery);
    }
    else {

    // for (uint8_t i = 0; i < 16; i++) {

    //     Sprites::drawSelfMasked(0, (i * 8) - yOffset, Images::Background, i);

    // }

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
    
    // if (gameStats.numberOfLivesLeft >= 3) {
    //     Sprites::drawErase(27, 118 - yOffset, Images::Junior_Walking_L_1_Mask, 0);
    //     Sprites::drawSelfMasked(27, 118 - yOffset, Images::Junior_Walking_L_1, 0);
    // }

    // if (gameStats.numberOfLivesLeft >= 2) {
    //     Sprites::drawErase(44, 118 - yOffset, Images::Junior_Walking_L_1_Mask, 0);
    //     Sprites::drawSelfMasked(44, 118 - yOffset, Images::Junior_Walking_L_1, 0);
    // }

    // uint8_t digits[4] = {};
    // extractDigits(digits, gameStats.score);

    // Sprites::drawErase(81, 118 - yOffset, Images::Game_Icon_Mask, 0);
    // Sprites::drawSelfMasked(81, 118 - yOffset, Images::Game_Icon, 0);

    // for (uint8_t j = 4; j > 0; --j) {

    //     Sprites::drawErase(122 - (j*7), 120 - yOffset, Images::Numbers, digits[j - 1]);

    // }

}


bool Game::playGame_GetPaused() {

  return playGameVars.paused;

}

void Game::playGame_SetPaused(bool value) {
  
  playGameVars.paused = value;

}

void Game::playGame_HandleCommonButtons() {

    // auto justPressed = arduboy.justPressedButtons();

    // if (gameStats.gameOver) {

    //     if (PC::buttons.pressed(BTN_A)) {
    //         gameState = GameStateType::HighScore_Activate; 
    //     }

    // }
    // else {

    //     if (PC::buttons.pressed(BTN_B)) {
    //         playGameVars.paused = !playGameVars.paused; 
    //     }

    // }

}

void Game::playGame_RenderGameOverOrPause() {


  // Game Over?

//   if (gameStats.gameOver) {

//     Sprites::drawExternalMask(28, 13, Images::GameOver, Images::GameOver_Mask, 0, 0); 

//   }

//   // Pause?

//   if (playGameVars.paused) {

//     Sprites::drawExternalMask(39, 16, Images::Pause, Images::Pause_Mask, 0, 0); 

//   }

}
