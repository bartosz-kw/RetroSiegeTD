#include "wavecounter.hpp"
#include "../utility/debugUtil.hpp"
#include "../managers/wavemanager.hpp"
#include "../managers/guimanager.hpp"
#include <cassert>


void WaveCounter::InitLabels()
{
    TextLabel& waveCountLabel = mgr_gui->AddLabel(TextLabel{});
    waveCountLabel.p_text = "Wave:";
    waveCountLabel.p_id = mgr_gui->GetAmountOfLabels();
    waveCountLabel.p_fontSize = GetFontDefault().baseSize;
    waveCountLabel.p_rect = {5,3,95,20};
    waveCountLabel.p_color = GREEN;
    waveCountLabel.p_updateFunction = [this](float deltaTime , TextLabel& label)
    {
        EnemyWave* currentWave = mgr_wave->GetSmallestIdWave();
        TempMessage* currentMessage = mgr_wave->GetWaveMessage();
        assert(currentMessage != nullptr && "currentMessage shouldn't be a nullptr");
        if (!currentWave)
        {
            label.p_text = "Victory!";
            return;
        }
        else if(!currentMessage->p_message.empty())
        {
            currentMessage->p_time -= deltaTime;
            label.p_text = currentMessage->p_message;
            return;
        }
        
        std::string text = "Wave: " + std::to_string(currentWave->p_id);
        label.p_text = text;
    };
}

void WaveCounter::InjectDependencies(WaveManager* waveManager,GuiManager* guiManager)
{
    mgr_wave = waveManager;
    mgr_gui = guiManager;
}

void WaveCounter::Init()
{
    assert(mgr_gui != nullptr && "GuiManager wasn't injected and its dependency");
    assert(mgr_wave != nullptr && "WaveManager wasn't injected and its dependency");
    InitLabels();
}
