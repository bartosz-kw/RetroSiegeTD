#pragma once
#include <raylib.h>

#include "../context/viewport.hpp"
#include "../enums/gamestate.hpp"
#include "../gui/endgame.hpp"
#include "../gui/enemyhover.hpp"
#include "../gui/mainmenu.hpp"
#include "../gui/playerstats.hpp"
#include "../gui/popup.hpp"
#include "../gui/speed.hpp"
#include "../gui/towerplace.hpp"
#include "../gui/towerselect.hpp"
#include "../gui/wavecounter.hpp"
#include "../managers/animationmanager.hpp"
#include "../managers/bulletmanager.hpp"
#include "../managers/enemymanager.hpp"
#include "../managers/guimanager.hpp"
#include "../managers/messagemanager.hpp"
#include "../managers/musicmanager.hpp"
#include "../managers/particlemanager.hpp"
#include "../managers/playermanager.hpp"
#include "../managers/psmanager.hpp"
#include "../managers/tilemanager.hpp"
#include "../managers/towermanager.hpp"
#include "../managers/wavemanager.hpp"

class Game {
private:
    bool m_shutingDown = false;
    RenderTexture2D m_frame = {};
    GameState m_gameState = GameState::Menu;
    Viewport m_viewport = {};

    TileManager mgr_tile = {m_viewport};
    EnemyManager mgr_enemy = {m_viewport};
    TowerManager mgr_tower = {m_viewport};
    BulletManager mgr_bullet = {};
    WaveManager mgr_wave = {};
    GuiManager mgr_gui = GuiManager(m_viewport);
    PSManager mgr_ps = {};
    PlayerManager mgr_player = {};
    MusicManager mgr_music = {};
    ParticleManager mgr_particle = {};
    MessageManager mgr_message = {};
    AnimationManager mgr_animation = {};

    EnemyHover gui_enemyHover = {};
    MainMenu gui_mainMenu = {};
    WaveCounter gui_waveCounter = {};
    TowerSelect gui_towerSelect = {};
    TowerPlace gui_towerPlace = {};
    PlayerStats gui_playerStats = {};
    Speed gui_speed = {};
    Popup gui_popup = {};
    EndGame gui_endGame = {};

private:
    void HandleInput();
    void UpdateDebug();
    void Update();
    void MakeTextureFrame() const;
    void Draw();
    void InitManagers();
    void InitGui();
    void InitSprites();
    void InitAudio();
    void InitDatas();
    void InitMembers();
    void InitGame();

    void Shutdown();

public:
    const int p_virtualHeight = 270;
    const int p_virtualWidth = 480;

public:
    Game() = default;
    ~Game() = default;

    void StartGame();
    void CloseGame();

    void Init();
    void Restart();
    void Run();
};
