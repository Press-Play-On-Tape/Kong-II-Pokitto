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

    // #ifdef INCLUDE_SOUND 
    // Utils::playSoundEffect(SoundEffects::Silence);
    // #endif

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::splashScreen_Update() { 

    if (PC::buttons.pressed(BTN_A))  { this->gameState = GameStateType::TitleScreen_Activate; }


    auto justPressed = PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B) || PC::buttons.pressed(BTN_C);

    if (justPressed > 0) {

        this->gameState = GameStateType::TitleScreen_Activate; 

    }
    
    if (Utils::isFrameCount(12)) {
     
        splashScreenVars.counter++;
        
        if (splashScreenVars.counter == 4) {
            
            splashScreenVars.counter = 0;
            
        }
        
    }
    
}


// ----------------------------------------------------------------------------
//  Render the state ..
//
void Game::splashScreen_Render() {

    PD::drawBitmap(44, 54, Images_Normal::Ppot_Full);
    PD::drawBitmap(64, 76, Images_Normal::Ppot[splashScreenVars.counter]);

    if (splashScreenVars.counter < 2) PD::drawBitmap(163, 72, Images_Normal::Ppot_Arrow);

}
