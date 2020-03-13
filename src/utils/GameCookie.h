#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "Enums.h"

class GameCookie : public Pokitto::Cookie {
    
    public:
    
    	uint8_t initialised;
        uint16_t easyScore = 0;
        uint16_t hardScore = 0;
				uint16_t deadScore = 0;
		ViewSize viewSize = ViewSize::Normal;
		GameMode mode = GameMode::Easy;


	public:

		void initialise() {

			this->initialised = COOKIE_INITIALISED;

			this->easyScore = 0;
			this->hardScore = 0;
			this->deadScore = 0;
			this->viewSize = ViewSize::Normal;
			this->mode = GameMode::Easy;
			this->saveCookie();

		}

};
