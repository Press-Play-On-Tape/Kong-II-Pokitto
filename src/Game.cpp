#include "Game.h"
// #include "utils/Enums.h"
// #include "utils/Structs.h"
// #include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;


void Game::setup(GameCookie *cookie) { 
    
    this->cookie = cookie;
    	
}

void Game::loop(void) {
    
    PC::buttons.pollButtons();
    PD::clear();

    switch (gameState) {

        case GameStateType::SplashScreen_Activate:
            splashScreen_Activate();
            gameState = GameStateType::SplashScreen;
            [[fallthrough]];

        case GameStateType::SplashScreen:
            splashScreen_Update();
            splashScreen_Render();
            break;

        case GameStateType::TitleScreen_Activate:
            titleScreen_Activate();
            gameState = GameStateType::TitleScreen;
            [[fallthrough]];

        case GameStateType::TitleScreen:
            titleScreen_Update();
            titleScreen_Render();
            break;

        case GameStateType::PlayGame_Activate:
            playGame_Activate();
            gameState = GameStateType::PlayGame;
            [[fallthrough]];

        case GameStateType::PlayGame:
            playGame_Update();
            playGame_Render();
            break;

        default: break;

    }    

	
}
