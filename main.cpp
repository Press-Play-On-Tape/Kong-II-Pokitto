#include "Pokitto.h"
#include "PokittoCookie.h"

#include "src/utils/Utils.h"
#include "src/Game.h"
#include "src/utils/GameCookie.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;

Game game;
GameCookie cookie;


int main() {


    // Initialise pokitto ..

    cookie.begin("KONGII", sizeof(cookie), (char*)&cookie);

    PC::begin();
    PD::loadRGBPalette(palettePico);   
    PD::persistence = true;
    PD::setColor(5);
    PD::setInvisibleColor(14);
    PC::setFrameRate(70);

    #if POK_HIGH_RAM == HIGH_RAM_MUSIC
    memset(buffers[0], 128, BUFFER_SIZE);
    memset(buffers[1], 128, BUFFER_SIZE);
    memset(buffers[2], 128, BUFFER_SIZE);
    memset(buffers[3], 128, BUFFER_SIZE);
    #else
    memset(&(buffers[0]), 128, BUFFER_SIZE);
    memset(&(buffers[1]), 128, BUFFER_SIZE);
    memset(&(buffers[2]), 128, BUFFER_SIZE);
    memset(&(buffers[3]), 128, BUFFER_SIZE);
    #endif


    // Kick off the random number generator ..
    
    srand(time(0));



    // Has the cookie been initialised?  This modified version allows
    // the Game C score to be initialised without losing other scores.

    switch (cookie.initialised) {

        case COOKIE_INITIALISED:
            cookie.deadScore = 0;
            cookie.saveCookie();
            break;

        case COOKIE_INITIALISED + 1:
            // do nothing
            break;

        default:
            cookie.initialise();
            break;

    }



    // Play game!

    game.setup(&cookie);

    while (PC::isRunning()) {
    
        if (!PC::update()) continue;
    
        PC::sound.updateStream();
        game.loop();
    
    }
    
    return 0;

}



