#pragma once

#define PROJ_BUTTONS_POLLING_ONLY

#define PROJ_SCREENMODE             15
#define PROJ_HIGH_RAM               HIGH_RAM_MUSIC
#define PROJ_ENABLE_SFX             1
#define PROJ_AUD_FREQ               8000

#define INCLUDE_SOUND
#define INCLUDE_SOUND_FROM_SD

#ifdef INCLUDE_SOUND_FROM_SD

    #define PROJ_STREAM_LOOP            0
    #define PROJ_ENABLE_SD_MUSIC

#endif

// Comment out IGNORE_COLLISIONS to include colllision detection ..
//#define _IGNORE_COLLISIONS
#define _ONE_KEY_ONLY
#define _TWO_KEYS_ONLY
