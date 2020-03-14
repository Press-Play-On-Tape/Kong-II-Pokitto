#pragma once

namespace Images_Large {

    #include "birds/large/Birds.h"
    #include "clappers/large/Clappers.h"
    #include "keys/large/Keys.h"
    #include "kong/large/Kong.h"
    #include "player/large/Player.h"
    #include "scenery/large/Scenerys.h"
    #include "sparks/large/Sparks.h"
    #include "ppot/PPOT.h"
    #include "title/TitleScreen.h"
    #include "others/large/Others.h"
    #include "numbers/large/Numbers.h"

    const uint8_t * const PROGMEM Numbers[] = { 
    Number_0,
    Number_1,
    Number_2,
    Number_3,
    Number_4,
    Number_5,
    Number_6,
    Number_7,
    Number_8,
    Number_9,
    };

    const uint8_t * const PROGMEM Game_Icon[] = { 
    GameA,
    GameB,
    GameB
    };

    const uint8_t * const PROGMEM Birds[] = { 
    Bird_F0,
    Bird_F1,
    Bird_F2,
    Bird_F3,
    Bird_Upright,
    Bird_Turn_00,
    Bird_Turn_01,
    Bird_Turn_02,
    Bird_Turn_03,
    Bird_Turn_04,
    Bird_Turn_05,
    };

    const uint8_t * const PROGMEM Clappers[] = { 
    Clapper_F1,
    Clapper_F2,
    };

    const uint8_t * const PROGMEM Key_Spin[] = { 
    Key_Spin_F0,
    Key_Spin_F1,
    Key_Spin_F2,
    Key_Spin_F3,
    };

    const uint8_t * const PROGMEM Key_Rotate[] = { 
    Key_Rotate_F0,
    Key_Rotate_F1,
    Key_Rotate_F2,
    Key_Rotate_F3,
    Key_Rotate_F4,
    Key_Rotate_F5,
    Key_Rotate_F6,
    Key_Rotate_F7,
    };

    const uint8_t * const PROGMEM Lock_Chains[] = { 
    Lock_Chain_1,
    Lock_Chain_2,
    Lock_Chain_3,
    Lock_Chain_4,
    };

    const uint8_t * const PROGMEM Kong[] = { 
    Kong_Normal,
    Kong_Falling_F0,
    Kong_Falling_F1,
    Kong_FacingRight_F0,
    Kong_FacingRight_F1,
    Kong_FacingRight_F2,
    Kong_FacingRight_F3,
    };

    const uint8_t * const PROGMEM Junior[] = { 
    Jnr_Idle_L_F0,
    Jnr_Idle_R_F0,
    Jnr_Walking_L_F1,
    Jnr_Walking_L_F2,
    Jnr_Walking_R_F1,
    Jnr_Walking_R_F2,
    Jnr_OnRope_F0,
    Jnr_OnRope_F1,
    Jnr_OnRope_F2,
    Jnr_OnRope_F3,
    Jnr_Climbing_Vine_F0,
    Jnr_Climbing_Vine_F1,
    };

    const uint8_t * const PROGMEM Spark[] = { 
    Spark_F1,
    Spark_F2
    };

    const uint8_t * const PROGMEM Background[] = { 
    Scenery_00,
    Scenery_01,
    Scenery_02,
    Scenery_03,
    Scenery_04,
    Scenery_05,
    Scenery_06,
    Scenery_07,
    Scenery_08,
    Scenery_09,
    Scenery_10,
    Scenery_11,
    Scenery_12,
    Scenery_13,
    Scenery_14,
    Scenery_15,
    };

};
