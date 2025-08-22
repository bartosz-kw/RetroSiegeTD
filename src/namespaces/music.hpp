#pragma once
#include <raylib.h>

namespace GameMusic
{

    inline Music g_towerDefenseMain = {};

    inline void InitAudio()
    {
        InitAudioDevice();
    }

    inline void UpdateMusic()
    {
        constexpr bool disableMusic = true;
        if (disableMusic)
        {
            return;
        }
        
        if (IsMusicStreamPlaying(g_towerDefenseMain))
        {
            UpdateMusicStream(g_towerDefenseMain);
        }
    }

    inline void LoadSounds()
    {
    }
    inline void LoadMusic()
    {
        g_towerDefenseMain = LoadMusicStream("src/resources/audio/happy2.ogg");
    }

    inline void UnloadMusic()
    {
        UnloadMusicStream(g_towerDefenseMain);
    }

    inline void UnloadSounds()
    {
    }
}
