#include "playerstats.hpp"
#include "../utility/debugUtil.hpp"
#include "../namespaces/settings.hpp"
#include "../managers/wavemanager.hpp"
#include "../managers/guimanager.hpp"
#include "../managers/psmanager.hpp"
#include <cassert>


void PlayerStats::InitLabels()
{
    constexpr size_t amountOfLabels = 2;
    mgr_gui->ReserveLabel(amountOfLabels);

    #pragma region HealthLabel
    TextLabel& healthLabel = mgr_gui->AddLabel(TextLabel{});
    healthLabel.p_text = "Health:";
    healthLabel.p_id = mgr_gui->GetAmountOfLabels();
    healthLabel.p_rect = {5,28,95,20};
    healthLabel.p_color = RED;
    healthLabel.p_updateFunction = [this](float deltaTime,TextLabel& label)
    {
        const std::string text = "Hp: " + std::to_string(mgr_ps->GetHealth()) + "/" + std::to_string(mgr_ps->GetMaxHealth());
        label.p_text = text;
    };
    #pragma endregion

    #pragma region MoneyLabel
    TextLabel& moneyLabel = mgr_gui->AddLabel(TextLabel{});
    moneyLabel.p_text = "Wave:";
    moneyLabel.p_id = mgr_gui->GetAmountOfLabels();
    moneyLabel.p_rect = {5,53,95,20};
    moneyLabel.p_color = YELLOW;
    moneyLabel.p_updateFunction = [this](float deltaTime,TextLabel& label)
    {
        const std::string text = "$: " + std::to_string(mgr_ps->GetMoney());
        label.p_text = text;
    };
    #pragma endregion
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
