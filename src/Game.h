#pragma once

#include "Pokitto.h"
#include "utils/GameCookie.h"

#include "images/Images.h"
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

        // void PlayGame_Activate();
        // void PlayGame_Update();
        // void PlayGame_CheckLastKey(uint8_t chain);
        // void PlayGame_ScrollToBottom(bool renderKong);
        // void PlayGame_DrawScenery(uint8_t yOffset);
        // void PlayGame_KillPlayer();
        // void PlayGame_ResetLevel(uint8_t introDelay);
        // void PlayGame_RenderScore(uint8_t yOffset);
        // bool PlayGame_GetPaused();
        // void PlayGame_SetPaused(bool value);
        // void PlayGame_HandleCommonButtons();
        // void PlayGame_RenderGameOverOrPause();

        // void PlayGame_Render();
        // void PlayGame_RenderKong(uint8_t yOffset);
        // void PlayGame_RenderKey(uint8_t yOffset);

        // void HighScore_Activate();
        // void HighScore_Update();
        // void HighScore_RenderHighScore(uint16_t score);
        // void HighScore_Render();

    private:

        SplashScreenStateVars splashScreenVars;
        TitleScreenStateVars titleScreenVars;
        PlayGameStateVars playGameVars;
        HighScoreStateVars highScoreVars;

        GameStats gameStats;
        GameStateType gameState = GameStateType::SplashScreen_Activate; 

};