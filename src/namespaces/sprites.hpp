#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <raylib.h>

namespace Sprites
{
    // offset data
    inline constexpr int8_t g_tileTextureOffset = -1;
    inline constexpr uint8_t g_enemyTextureOffset = g_tileTextureOffset + 5;
    inline constexpr uint8_t g_towerTextureOffset = g_enemyTextureOffset + 2;
    inline constexpr uint8_t g_buttetTextureOffset = g_towerTextureOffset + 9;
    // texture array variables
    inline constexpr size_t g_textureAmount = 21;
    inline std::array<Texture2D,g_textureAmount> g_textures = {};

    inline void LoadTextures()
    { 
        g_textures[0] = LoadTexture("src/resources/sprites/GrassTile.png");
        g_textures[1] = LoadTexture("src/resources/sprites/GrassPathSprite1.png");
        g_textures[2] = LoadTexture("src/resources/sprites/GrassPathSprite2.png");
        g_textures[3] = LoadTexture("src/resources/sprites/GrassPathSprite3.png");
        g_textures[4] = LoadTexture("src/resources/sprites/GrassPathSprite4.png");
        g_textures[5] = LoadTexture("src/resources/sprites/BlueSlimeEnemy.png");
        g_textures[6] = LoadTexture("src/resources/sprites/RedSlimeEnemy.png");
        g_textures[7] = LoadTexture("src/resources/sprites/NinjaTower1.png");
        g_textures[8] = LoadTexture("src/resources/sprites/NinjaTower2.png"); 
        g_textures[9] = LoadTexture("src/resources/sprites/NinjaTower3.png");
        g_textures[10] = LoadTexture("src/resources/sprites/NinjaTower4.png");
        g_textures[11] = LoadTexture("src/resources/sprites/KnightTower1.png");
        g_textures[12] = LoadTexture("src/resources/sprites/KnightTower2.png");
        g_textures[13] = LoadTexture("src/resources/sprites/KnightTower3.png");
        g_textures[14] = LoadTexture("src/resources/sprites/KnightTower4.png");
        g_textures[15] = LoadTexture("src/resources/sprites/KnightTower5.png");
        g_textures[16] = LoadTexture("src/resources/sprites/ShulikenBullet.png");
        g_textures[17] = LoadTexture("src/resources/sprites/SharpShulikenBullet.png");
        g_textures[18] = LoadTexture("src/resources/sprites/DaggerBullet.png");
        g_textures[19] = LoadTexture("src/resources/sprites/SlashBullet.png");
        g_textures[20] = LoadTexture("src/resources/sprites/SpearSlashBullet.png");
    }
    inline void UnLoadTextures()
    {
        for (size_t i = 0; i < g_textures.size(); i++)
        {
            UnloadTexture(g_textures[i]);
        }
    }
}