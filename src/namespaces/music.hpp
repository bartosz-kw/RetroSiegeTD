#pragma once
#include <raylib.h>

namespace Music
{
    inline Sound g_towerPlaceSound = {};

    inline void LoadSounds()
    {
        g_towerPlaceSound = LoadSound("src/resources/audio/towerplace.ogg");
    }

    inline void UnloadSounds()
    {
        UnloadSound(g_towerPlaceSound);
    }

}
