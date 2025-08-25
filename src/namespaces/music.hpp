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
        g_towerDefenseMain = LoadMusicStream("src/resources/audio/calm1.ogg");
        SetMusicVolume(g_towerDefenseMain, 0.15f);
        g_towerDefenseMenu = LoadMusicStream("src/resources/audio/calm2.ogg");
        SetMusicVolume(g_towerDefenseMenu, 0.15f);
    }

    inline void UnloadMusic()
    {
        if (g_towerDefenseMain.ctxData)
        {
            if (IsMusicStreamPlaying(g_towerDefenseMain))
                StopMusicStream(g_towerDefenseMain);
            UnloadMusicStream(g_towerDefenseMain);
            g_towerDefenseMain = {};
        }

        if (g_towerDefenseMenu.ctxData)
        {
            if (IsMusicStreamPlaying(g_towerDefenseMenu))
                StopMusicStream(g_towerDefenseMenu);
            UnloadMusicStream(g_towerDefenseMenu);
            g_towerDefenseMenu = {};
        }
    }

    inline void UnloadSounds()
    {
    }

    inline void UnloadAudio()
    {
        CloseAudioDevice();
    }
}
