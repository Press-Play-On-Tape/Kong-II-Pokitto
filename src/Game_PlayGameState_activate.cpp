#include "Game.h"
#include "Pokitto.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void Game::playGame_Activate() {

    this->playGameVars.player.reset(this->cookie->viewSize);

		switch (cookie->mode) {
			case GameMode::Easy:
				this->playGameVars.clappersLowerDelay = CLAPPERS_LOWER_MAX_EASY;
				this->playGameVars.clappersUpperDelay = CLAPPERS_UPPER_MAX_EASY;
				this->playGameVars.sparksUpperDelay = SPARKS_LOWER_MAX_EASY;
				this->playGameVars.sparksUpperDelay = SPARKS_UPPER_MAX_EASY;
				this->playGameVars.birdsDelay = BIRDS_MAX_EASY;
				break;
			case GameMode::Hard:
				this->playGameVars.clappersLowerDelay = CLAPPERS_LOWER_MAX_HARD;
				this->playGameVars.clappersUpperDelay = CLAPPERS_UPPER_MAX_HARD;
				this->playGameVars.sparksUpperDelay = SPARKS_LOWER_MAX_HARD;
				this->playGameVars.sparksUpperDelay = SPARKS_UPPER_MAX_HARD;
				this->playGameVars.birdsDelay = BIRDS_MAX_HARD;
				break;
			case GameMode::Dead:
				this->playGameVars.clappersLowerDelay = CLAPPERS_LOWER_MAX_DEAD;
				this->playGameVars.clappersUpperDelay = CLAPPERS_UPPER_MAX_DEAD;
				this->playGameVars.sparksUpperDelay = SPARKS_LOWER_MAX_DEAD;
				this->playGameVars.sparksUpperDelay = SPARKS_UPPER_MAX_DEAD;
				this->playGameVars.birdsDelay = BIRDS_MAX_DEAD;
				break;
		}

    this->playGameVars.lowerClappers.setDelayMax(this->playGameVars.clappersLowerDelay, true);
    this->playGameVars.lowerClappers.reset(this->cookie->viewSize, 107);

    this->playGameVars.upperClappers.setDelayMax(this->playGameVars.clappersUpperDelay, true);
    this->playGameVars.upperClappers.reset(this->cookie->viewSize, 54);

    this->playGameVars.lowerSparks.setDelayMax(this->playGameVars.sparksUpperDelay, true);
    this->playGameVars.lowerSparks.reset(Coordinates::LowerSpark);

    this->playGameVars.upperSparks.setDelayMax(this->playGameVars.sparksUpperDelay, true);
    this->playGameVars.upperSparks.reset(Coordinates::UpperSpark);

    this->playGameVars.birds.setDelayMax(this->playGameVars.birdsDelay, true);
    this->playGameVars.birds.reset();

    this->playGameVars.kong.reset();

    this->playGameVars.frameRate = FRAME_RATE_MIN;
    this->playGameVars.pauseMenu = 0;
    PC::setFrameRate(this->playGameVars.frameRate);

    playGame_ResetLevel(INTRO_DELAY_FROM_TITLE_SCROLL);
    this->playGameVars.key.setKeyLocation(KeyLocation::LowerPosition);  

    this->playGameVars.playing = false;
    this->playGameVars.exitSequence = false;
    
    this->playGameVars.paused = false;

    #ifdef INCLUDE_SOUND 
    Utils::playMusicStream(SoundEffects::Introduction);
    #endif

}
