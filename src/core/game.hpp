#pragma once
#include <raylib.h>
#include "../managers/tilemanager.hpp"
#include "../managers/enemymanager.hpp"
#include "../managers/towermanager.hpp"
#include "../managers/bulletmanager.hpp"
#include "../managers/wavemanager.hpp"
#include "../managers/guimanager.hpp"
#include "../managers/psmanager.hpp"
#include "../managers/playermanager.hpp"
#include "../gui/wavecounter.hpp"
#include "../gui/towerselect.hpp"
#include "../gui/towerplace.hpp"
#include "../gui/playerstats.hpp"

class Game
{
private: 
    // variables
    RenderTexture2D     m_frame = {};
    bool       m_gameStarted = false;
    // managers
    TileManager        mgr_tile = {};
    EnemyManager      mgr_enemy = {};
    TowerManager      mgr_tower = {};
    BulletManager    mgr_bullet = {};
    WaveManager        mgr_wave = {};
    GuiManager          mgr_gui = {};
    PSManager            mgr_ps = {};
    PlayerManager    mgr_player = {};
    // gui
    WaveCounter gui_waveCounter = {};
    TowerSelect gui_towerSelect = {};
    TowerPlace   gui_towerPlace = {};
    PlayerStats gui_playerStats = {};

private: // functions 

    void UpdateDebug();
    void Update();
    void MakeTextureFrame() const;
    void Draw()             const;

    void StartGame();

    void InitManagers();
    void InitGui();
    void InitSprites();
    void InitMusic();
    void InitDatas();
    void InitMembers();
    void InitGame();

public: // variables
    const int p_gameHeight    = 270;
    const int p_gameWidth     = 480;
    const int p_scaledHeight = 1080;
    const int p_scaledWidth  = 1920;
    const int p_screenHeight = 1080;
    const int p_screenWidth  = 1920;

public: // functions
    Game()  = default;
    ~Game() = default;

    void Init();
    void Run();
    void Shutdown();
};