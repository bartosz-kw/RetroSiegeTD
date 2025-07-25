#pragma once
#include <raylib.h>
#include "../managers/tilemanager.hpp"
#include "../managers/enemymanager.hpp"
class Game
{
private: // variables
    Font m_mainFont = {};
    RenderTexture2D m_frame = {};
    // managers
    TileManager mgr_tile = {};
    EnemyManager mgr_enemy = {};
private: // functions
    void UpdateDebug();
    void Update();
    void MakeTextureFrame() const;
    void Draw() const;

public: // variables
    const int p_gameHeight = 270;
    const int p_gameWidth = 480;    
    const int p_scaledHeight = 1080;
    const int p_scaledWidth = 1920;
    const int p_screenHeight = 1080;
    const int p_screenWidth = 1920;
public: // functions
    Game() = default;
    ~Game() = default;
    void Init();
    void Run();
    void Shutdown();
};