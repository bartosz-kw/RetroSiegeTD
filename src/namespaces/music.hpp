#pragma once
#include <raylib.h>

namespace GameMusic
{
    inline Sound g_towerPlaceSound = {};

    inline void InitAudio()
    {
        InitAudioDevice();
    }
    
    inline void LoadSounds()
    {
        g_towerPlaceSound = LoadSound("src/resources/audio/towerplace.wav");
    }

    inline void UnloadSounds()
    {
        UnloadSound(g_towerPlaceSound);
    }
}
