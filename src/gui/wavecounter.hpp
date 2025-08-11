#include "../structs/textlabel.hpp"

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
    void InitLabels();
    
public:
    void InjectDependencies(WaveManager* waveManager,GuiManager* guiManager,PlayerManager* playerManager);
    void Init();
};
