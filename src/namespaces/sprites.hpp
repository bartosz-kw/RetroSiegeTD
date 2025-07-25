#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <raylib.h>

namespace Sprites
{
    // offset data
    inline constexpr int8_t tileTextureOffset = -1;
    inline constexpr uint8_t enemyTextureOffset = 2;
    // texture array variables
    inline constexpr size_t p_textureAmount = 4;
    inline std::array<Texture2D,p_textureAmount> g_textures = {};

    inline void LoadTextures()
    {
        g_textures[0] = LoadTexture("src/resources/sprites/GrassTile.png");
        g_textures[1] = LoadTexture("src/resources/sprites/GrassPathSprite1.png");
        g_textures[2] = LoadTexture("src/resources/sprites/GrassPathSprite2.png");
        g_textures[3] = LoadTexture("src/resources/sprites/SlimeEnemy.png");
    }
    inline void UnLoadTextures()
    {
        for (size_t i = 0; i < g_textures.size(); i++)
        {
            UnloadTexture(g_textures[i]);
        }
    }
}