#include "Game.h"
#include "Pokitto.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;



// ----------------------------------------------------------------------------
//  Initialise state ..
//
void Game::titleScreen_Activate() {

    gameStats.resetGame();
    
    //sound.volumeMode(VOLUME_ALWAYS_NORMAL);

    playGameVars.frameRate = FRAME_RATE_MIN;
    PC::setFrameRate(playGameVars.frameRate);

    titleScreenVars.restart = 0;
    titleScreenVars.counter = 0;
    titleScreenVars.position = Rotation::None;

    #ifdef PLAY_SOUNDS 
    sound.tones(Sounds::TitleMusic);
    #endif

}


// ----------------------------------------------------------------------------
//  Handle state updates ..
//

void Game::titleScreen_Update() {

    if (PC::buttons.pressed(BTN_A)) { 

        this->gameState = GameStateType::PlayGame_Activate; 

    }

    if (PC::buttons.pressed(BTN_C)) { 

        this->gameStats.viewSize = ViewSize::Large;
        this->gameState = GameStateType::PlayGame_Activate; 

    }

}


// ----------------------------------------------------------------------------
//  Render the state ..
//
void Game::titleScreen_Render() {

    PD::drawBitmap(0, 0, Images_Normal::TitleScreen, false, false);

}
