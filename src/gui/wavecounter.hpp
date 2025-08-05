#include "../structs/textlabel.hpp"

class WaveManager; // Forward declaration
class GuiManager;
class WaveCounter
{
private:
    WaveManager* mgr_wave = nullptr;
    GuiManager* mgr_gui = nullptr;
private:
    void InitLabels();
    
public:
    void InjectDependencies(WaveManager* waveManager,GuiManager* guiManager);
    void Init();
};
