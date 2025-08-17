#include "wavecounter.hpp"
#include "../namespaces/settings.hpp"
#include "../utility/debugUtil.hpp"
#include "../managers/wavemanager.hpp"
#include "../managers/guimanager.hpp"
#include "../managers/playermanager.hpp"
#include <cassert>

void WaveCounter::InitButtons()
{
    constexpr size_t amountOfButtons = 1;
    mgr_gui->ReserveButton(amountOfButtons);

#pragma region WaveCountButton
    Button &waveCountButton = mgr_gui->AddButton(Button{});
    waveCountButton.p_text = "Wave:";
    waveCountButton.p_id = mgr_gui->GetAmountOfButtons();
    waveCountButton.p_rect = {5, 3, 95, 20};
    waveCountButton.p_color = GREEN;
    waveCountButton.p_isHovered = false;
    waveCountButton.p_visible = true;
    waveCountButton.p_onPressed = [this](float deltaTime, Button &button)
    {
        if (mgr_wave->IsSkipAllowed())
        {
            mgr_wave->SkipWave();
        }
        
    };
    waveCountButton.p_updateFunction = [this](float deltaTime, Button &button)
    {
        const EnemyWave *currentWave = mgr_wave->GetCurrentWave();
        TempMessage *currentMessage = mgr_wave->GetWaveMessage();
        assert(currentMessage != nullptr && "currentMessage shouldn't be a nullptr");
        if (!currentWave && mgr_player->IsGameOver())
        {
            button.p_text = "You lost.";
            return;
        }
        else if (!currentWave)
        {
            button.p_text = "Victory!";
            return;
        }
        else if (mgr_wave->IsSkipAllowed())
        {
            button.p_text = "Skip Wave " + std::to_string(currentWave->p_id);
            return;
        }
        else if (!currentMessage->p_message.empty())
        {
            currentMessage->p_time -= deltaTime;
            button.p_text = currentMessage->p_message;
            return;
        }

        const std::string text = "Wave: " + std::to_string(currentWave->p_id);
        button.p_text = text;
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
    InitButtons();
}
