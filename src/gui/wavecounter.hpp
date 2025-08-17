
class PlayerManager;
class WaveManager; 
class GuiManager;
class WaveCounter
{
private:
    PlayerManager* mgr_player = nullptr;
    WaveManager* mgr_wave = nullptr;
    GuiManager* mgr_gui = nullptr;
private:
    void InitButtons();
    
public:
    void InjectDependencies(WaveManager* waveManager,GuiManager* guiManager,PlayerManager* playerManager);
    void Init();
};
