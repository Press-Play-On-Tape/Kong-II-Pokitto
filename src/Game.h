#pragma once

#include "Pokitto.h"
#include "utils/GameCookie.h"

#include "images/Images_Normal.h"
#include "images/Images_Large.h"
#include "utils/Enums.h"
#include "entities/Entities.h"
#include "utils/Utils.h"
#include "utils/Structs.h"

class Game {
    
    public:

        void setup(GameCookie *cookie);
        void loop(void);

        void splashScreen_Activate();
        void splashScreen_Update();
        void splashScreen_Render();
        
        void titleScreen_Activate();
        void titleScreen_Update();
        void titleScreen_Render();

        void playGame_Activate();
        void playGame_Update();
        void playGame_CheckLastKey(uint8_t chain);
        void playGame_ScrollToBottom(bool renderKong);
        void playGame_DrawScenery(uint8_t yOffset);
        void playGame_KillPlayer();
        void playGame_ResetLevel(uint8_t introDelay);
        void playGame_RenderScore(uint8_t yOffset);
        bool playGame_GetPaused();
        void playGame_SetPaused(bool value);
        void playGame_HandleCommonButtons();
        void playGame_RenderGameOverOrPause();

        void playGame_Render();
        void playGame_RenderKong(uint8_t yOffset);
        void playGame_RenderKey(uint8_t yOffset);

        void highScore_Activate();
        void highScore_Update();
        void highScore_RenderHighScore(uint16_t score);
        void highScore_Render();

    private:

        SplashScreenStateVars splashScreenVars;
        TitleScreenStateVars titleScreenVars;
        PlayGameStateVars playGameVars;
        HighScoreStateVars highScoreVars;

        GameStats gameStats;
        GameStateType gameState = GameStateType::SplashScreen_Activate; 

};