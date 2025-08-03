#pragma once
#include <raylib.h>
#include "../managers/tilemanager.hpp"
#include "../managers/enemymanager.hpp"
#include "../managers/towermanager.hpp"
#include "../managers/bulletmanager.hpp"
#include "../managers/wavemanager.hpp"
#include "../gui/wavecounter.hpp"
#include "../gui/towerselect.hpp"

class Game
{
private: // variables
    Font m_mainFont = {};
    RenderTexture2D m_frame = {};
    // managers
    TileManager mgr_tile = {};
    EnemyManager mgr_enemy = {};
    TowerManager mgr_tower = {};
    BulletManager mgr_bullet = {};
    WaveManager mgr_wave = {};
    // gui
    WaveCounter gui_waveCounter = {};
    TowerSelect gui_towerSelect = {};

private: // functions
    void UpdateDebug();
    void Update();
    void MakeTextureFrame() const;
    void Draw() const;

    void InitManagers();
    void InitGui();
    void InitSprites();
    void InitMembers();
    void InitGame();

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