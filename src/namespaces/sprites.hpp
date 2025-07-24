#pragma once
#include <array>
#include <cstddef>
#include <raylib.h>

namespace Sprites
{
    inline std::array<Texture2D,1> g_textures = {};

    inline void LoadTextures()
    {
        g_textures[0] = LoadTexture("src/resources/sprites/GrassTile.png");

    }
    inline void UnLoadTextures()
    {
        for (size_t i = 0; i < g_textures.size(); i++)
        {
            UnloadTexture(g_textures[i]);
        }
    }
}