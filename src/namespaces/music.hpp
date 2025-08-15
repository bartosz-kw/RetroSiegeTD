#pragma once
#include <raylib.h>

namespace GameMusic
{
    inline Sound g_towerPlaceSound = {};

    inline Music g_towerDefenseMain = {};
    inline Music g_towerDefenseBoss = {};

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
        if (IsMusicStreamPlaying(g_towerDefenseBoss))
        {
            UpdateMusicStream(g_towerDefenseBoss);
        }
    }

    inline void LoadSounds()
    {
        g_towerPlaceSound = LoadSound("src/resources/audio/towerplace.wav");
    }
    inline void LoadMusic()
    {
        g_towerDefenseMain = LoadMusicStream("src/resources/audio/towerdefensemain.ogg");
        g_towerDefenseBoss = LoadMusicStream("src/resources/audio/bosstheme.wav");
    }

    inline void UnloadSounds()
    {
        UnloadSound(g_towerPlaceSound);
    }
}
