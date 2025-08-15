#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <raylib.h>

namespace Sprites
{
    // offset data
    inline constexpr int8_t g_tileTextureOffset = -1;
    inline constexpr uint8_t g_enemyTextureOffset = 4;
    inline constexpr uint8_t g_towerTextureOffset = 6;
    inline constexpr uint8_t g_buttetTextureOffset = 11;
    // texture array variables
    inline constexpr size_t g_textureAmount = 16;
    inline std::array<Texture2D,g_textureAmount> g_textures = {};

    inline void LoadTextures()
    {
        g_textures[0] = LoadTexture("src/resources/sprites/GrassTile.png");
        g_textures[1] = LoadTexture("src/resources/sprites/GrassPathSprite1.png");
        g_textures[2] = LoadTexture("src/resources/sprites/GrassPathSprite2.png");
        g_textures[3] = LoadTexture("src/resources/sprites/GrassPathSprite3.png");
        g_textures[4] = LoadTexture("src/resources/sprites/GrassPathSprite4.png");
        g_textures[5] = LoadTexture("src/resources/sprites/BlueSlimeEnemy.png");
        g_textures[6] = LoadTexture("src/resources/sprites/BlueSlimeEnemy.png");
        g_textures[7] = LoadTexture("src/resources/sprites/NinjaTower1.png");
        g_textures[8] = LoadTexture("src/resources/sprites/NinjaTower2.png"); 
        g_textures[9] = LoadTexture("src/resources/sprites/NinjaTower3.png");
        g_textures[10] = LoadTexture("src/resources/sprites/NinjaTower4.png");
        g_textures[11] = LoadTexture("src/resources/sprites/KnightTower1.png");
        g_textures[12] = LoadTexture("src/resources/sprites/ShulikenBullet.png");
        g_textures[13] = LoadTexture("src/resources/sprites/SharpShulikenBullet.png");
        g_textures[14] = LoadTexture("src/resources/sprites/DaggerBullet.png");
        g_textures[15] = LoadTexture("src/resources/sprites/SlashBullet.png");
    }
    inline void UnLoadTextures()
    {
        for (size_t i = 0; i < g_textures.size(); i++)
        {
            UnloadTexture(g_textures[i]);
        }
    }
}