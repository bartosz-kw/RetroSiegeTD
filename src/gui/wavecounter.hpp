#include "../structs/tempmessage.hpp"

class PlayerManager;
class WaveManager;
class GuiManager;
class WaveCounter
{
private:
    PlayerManager *mgr_player = nullptr;
    WaveManager *mgr_wave = nullptr;
    GuiManager *mgr_gui = nullptr;

    TempMessage m_message = {};

private:
    void InitButtons();

public:
    TempMessage &GetMessage();
    void SetMessage(const std::string message, const float time);
    void InjectDependencies(WaveManager *waveManager, GuiManager *guiManager, PlayerManager *playerManager);
    void Init();
};
