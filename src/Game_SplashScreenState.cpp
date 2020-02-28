#include "Game.h"
#include "Pokitto.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;



// ----------------------------------------------------------------------------
//  Initialise state ..
//
void Game::splashScreen_Activate() {

  splashScreenVars.counter = 0;

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::splashScreen_Update() { 

    if (PC::buttons.pressed(BTN_A))  { this->gameState = GameStateType::TitleScreen_Activate; }

}


// ----------------------------------------------------------------------------
//  Render the state ..
//
void Game::splashScreen_Render() {

    if (Utils::isFrameCount(12)) {
     
        splashScreenVars.counter++;
        
        if (splashScreenVars.counter == 4) {
            
            splashScreenVars.counter = 0;
            
        }
        
    }
    
    PD::drawBitmap(38, 48, Images_Normal::PPOT[splashScreenVars.counter]);

}
