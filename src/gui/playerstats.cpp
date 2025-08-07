#include "playerstats.hpp"
#include "../utility/debugUtil.hpp"
#include "../managers/wavemanager.hpp"
#include "../managers/guimanager.hpp"
#include "../managers/psmanager.hpp"
#include <cassert>


void PlayerStats::InitLabels()
{
    TextLabel& waveCountLabel = mgr_gui->AddLabel(TextLabel{});
    waveCountLabel.p_text = "Wave:";
    waveCountLabel.p_id = mgr_gui->GetAmountOfLabels();
    waveCountLabel.p_fontSize = GetFontDefault().baseSize;
    waveCountLabel.p_rect = {0,28,105,20};
    waveCountLabel.p_color = GREEN;
    waveCountLabel.p_updateFunction = [this](TextLabel& label)
    {
        std::string text = "$: " + std::to_string(mgr_ps->GetMoney());
        label.p_text = text;
    };
}
void PlayerStats::InjectDependencies(GuiManager* guiManager,PSManager* psManager)
{
    mgr_gui = guiManager;
    mgr_ps = psManager;
}
void PlayerStats::Init()
{
    //assert(mgr_wave != nullptr && "WaveManager wasn't injected and its dependency");
    assert(mgr_gui != nullptr && "GuiManager wasn't injected and its dependency");
    InitLabels();
}
