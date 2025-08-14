#pragma once
#include <raylib.h>

namespace GameMusic
{
    inline Sound g_towerPlaceSound = {};

    inline Music g_towerDefenseMain = {};

    inline void InitAudio()
    {
        InitAudioDevice();
    }

    inline void UpdateMusic()
    {
        if (IsMusicStreamPlaying(g_towerDefenseMain))
        {
            UpdateMusicStream(g_towerDefenseMain);
        }
    }

    inline void LoadSounds()
    {
        g_towerPlaceSound = LoadSound("src/resources/audio/towerplace.wav");
    }
    inline void LoadMusic()
    {
        g_towerDefenseMain = LoadMusicStream("src/resources/audio/towerdefensemain.ogg");
    }

    inline void UnloadSounds()
    {
        UnloadSound(g_towerPlaceSound);
    }
}
