#include "wavecounter.hpp"
#include "../namespaces/settings.hpp"
#include "../utility/debugUtil.hpp"
#include "../managers/wavemanager.hpp"
#include "../managers/guimanager.hpp"
#include "../managers/playermanager.hpp"
#include <cassert>

void WaveCounter::InitLabels()
{
    constexpr size_t amountOfLabels = 1;
    mgr_gui->ReserveLabel(amountOfLabels);

#pragma region WaveCountLabel
    TextLabel &waveCountLabel = mgr_gui->AddLabel(TextLabel{});
    waveCountLabel.p_text = "Wave:";
    waveCountLabel.p_id = mgr_gui->GetAmountOfLabels();
    waveCountLabel.p_rect = {5, 3, 95, 20};
    waveCountLabel.p_color = GREEN;
    waveCountLabel.p_updateFunction = [this](float deltaTime, TextLabel &label)
    {
        const EnemyWave *currentWave = mgr_wave->GetSmallestIdWave();
        TempMessage *currentMessage = mgr_wave->GetWaveMessage();
        assert(currentMessage != nullptr && "currentMessage shouldn't be a nullptr");
        if (!currentWave && mgr_player->IsGameOver())
        {
            label.p_text = "You lost.";
            return;
        }
        else if (!currentWave)
        {
            label.p_text = "Victory!";
            return;
        }
        else if (!currentMessage->p_message.empty())
        {
            currentMessage->p_time -= deltaTime;
            label.p_text = currentMessage->p_message;
            return;
        }

        const std::string text = "Wave: " + std::to_string(currentWave->p_id);
        label.p_text = text;
    };
#pragma endregion
}
void WaveCounter::InjectDependencies(WaveManager *waveManager, GuiManager *guiManager, PlayerManager *playerManager)
{
    mgr_wave = waveManager;
    mgr_gui = guiManager;
    mgr_player = playerManager;
}
void WaveCounter::Init()
{
    assert(mgr_gui != nullptr && "GuiManager wasn't injected and its dependency");
    assert(mgr_wave != nullptr && "WaveManager wasn't injected and its dependency");
    InitLabels();
}
