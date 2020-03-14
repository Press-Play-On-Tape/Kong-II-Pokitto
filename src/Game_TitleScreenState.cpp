#include "Game.h"
#include "Pokitto.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;



// ----------------------------------------------------------------------------
//  Initialise state ..
//
void Game::titleScreen_Activate() {

    this->gameStats.resetGame();
    
    //sound.volumeMode(VOLUME_ALWAYS_NORMAL);

    this->playGameVars.frameRate = FRAME_RATE_MIN;
    PC::setFrameRate(this->playGameVars.frameRate);

    titleScreenVars.position = static_cast<uint8_t>(cookie->mode);

}


// ----------------------------------------------------------------------------
//  Handle state updates ..
//

void Game::titleScreen_Update() {

    if (PC::buttons.pressed(BTN_UP) && titleScreenVars.position > 0) { 

        titleScreenVars.position--;

    }

    if (PC::buttons.pressed(BTN_DOWN) && titleScreenVars.position < 3) { 

        titleScreenVars.position++;

    }

    if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B) || PC::buttons.pressed(BTN_C)) { 

        switch (titleScreenVars.position) {
            
            case 0:
                this->cookie->mode = GameMode::Easy;
                this->cookie->saveCookie();
                this->gameState = GameStateType::PlayGame_Activate; 
                break;
            
            case 1:
                this->cookie->mode = GameMode::Hard;
                this->cookie->saveCookie();
                this->gameState = GameStateType::PlayGame_Activate; 
                break;
                
			case 2:
				this->cookie->mode = GameMode::Dead;
				this->cookie->saveCookie();
				this->gameState = GameStateType::PlayGame_Activate;
				break;
         
            case 3:
                this->cookie->viewSize = (this->cookie->viewSize == ViewSize::Normal ? ViewSize::Large : ViewSize::Normal);
                this->cookie->saveCookie();
                break;     
            
        }

    }

    if ((PC::buttons.pressed(BTN_LEFT) || PC::buttons.pressed(BTN_RIGHT)) && titleScreenVars.position == 3) { 

        this->cookie->viewSize = (this->cookie->viewSize == ViewSize::Normal ? ViewSize::Large : ViewSize::Normal);
        this->cookie->saveCookie();

    }

}


// ----------------------------------------------------------------------------
//  Render the state ..
//
void Game::titleScreen_Render() {

    const uint8_t yPos[] = { 13, 26, 39, 52};

    PD::drawBitmap(0, 0, Images_Normal::TitleScreen, false, false);
    PD::drawBitmap(106, yPos[titleScreenVars.position], Images_Normal::Selector, false, false);

    if (this->cookie->viewSize == ViewSize::Normal) {
        PD::drawBitmap(170, 48, Images_Normal::Full);
    }
    else {
        PD::drawBitmap(170, 48, Images_Normal::Zoom);
    }


    // Easy score ..

    uint8_t digits[4] = {};
    Utils::extractDigits(digits, this->cookie->easyScore);

    for (uint8_t j = 4; j > 0; --j) {

        PD::drawBitmap(77 - (j*5), 31, Images_Normal::HSNumbers[digits[j - 1]]);

    }


    // Hard score ..

    Utils::extractDigits(digits, this->cookie->hardScore);

    for (uint8_t j = 4; j > 0; --j) {

        PD::drawBitmap(77 - (j*5), 40, Images_Normal::HSNumbers[digits[j - 1]]);

    }


    // Hard score ..

    Utils::extractDigits(digits, this->cookie->deadScore);

    for (uint8_t j = 4; j > 0; --j) {

        PD::drawBitmap(77 - (j*5), 49, Images_Normal::HSNumbers[digits[j - 1]]);

    }

}
