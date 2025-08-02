#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <raylib.h>

namespace Sprites
{
    // offset data
    inline constexpr int8_t tileTextureOffset = -1;
    inline constexpr uint8_t enemyTextureOffset = 4;
    inline constexpr uint8_t towerTextureOffset = 5;
    inline constexpr uint8_t buttetTextureOffset = 6;
    // texture array variables
    inline constexpr size_t p_textureAmount = 8;
    inline std::array<Texture2D,p_textureAmount> g_textures = {};

    inline void LoadTextures()
    {
        g_textures[0] = LoadTexture("src/resources/sprites/GrassTile.png");
        g_textures[1] = LoadTexture("src/resources/sprites/GrassPathSprite1.png");
        g_textures[2] = LoadTexture("src/resources/sprites/GrassPathSprite2.png");
        g_textures[3] = LoadTexture("src/resources/sprites/GrassPathSprite3.png");
        g_textures[4] = LoadTexture("src/resources/sprites/GrassPathSprite4.png");
        g_textures[5] = LoadTexture("src/resources/sprites/BlueSlimeEnemy.png");
        g_textures[6] = LoadTexture("src/resources/sprites/NinjaTower.png");
        g_textures[7] = LoadTexture("src/resources/sprites/ShulikenBullet.png");
    }
    inline void UnLoadTextures()
    {
        for (size_t i = 0; i < g_textures.size(); i++)
        {
            UnloadTexture(g_textures[i]);
        }
    }
}