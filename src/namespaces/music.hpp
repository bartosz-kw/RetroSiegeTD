#pragma once
#include <raylib.h>

namespace GameMusic
{
    inline bool g_playMusic = true;

    inline Music g_towerDefenseMain = {};
    inline Music g_towerDefenseMenu = {};

    inline void InitAudio()
    {
        InitAudioDevice();
    }

    inline void UpdateMusic()
    {
        if (g_playMusic)
        {
            return;
        }
        
        if (IsMusicStreamPlaying(g_towerDefenseMain))
        {
            UpdateMusicStream(g_towerDefenseMain);
        }
        if (IsMusicStreamPlaying(g_towerDefenseMenu))
        {
            UpdateMusicStream(g_towerDefenseMenu);
        }
    }

    inline void LoadSounds()
    {
    }
    inline void LoadMusic()
    {
        g_towerDefenseMain = LoadMusicStream("src/resources/audio/happy2.ogg");
        g_towerDefenseMenu = LoadMusicStream("src/resources/audio/calm1.ogg");
    }

    inline void UnloadMusic()
    {
        UnloadMusicStream(g_towerDefenseMain);
    }

    inline void UnloadSounds()
    {
    }
}
