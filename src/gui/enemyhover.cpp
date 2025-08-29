#include "enemyhover.hpp"
#include "../utility/colorutil.hpp"
#include "../namespaces/settings.hpp"
#include "../managers/enemymanager.hpp"
#include "../managers/guimanager.hpp"
#include <cassert>

void EnemyHover::InitLabels()
{
    constexpr size_t amountOfLabels = 1;
    mgr_gui->ReserveLabel(amountOfLabels);

    #pragma region HealthLabel
    Label &healthLabel = mgr_gui->AddLabel(Label{});
    healthLabel.p_text = "";
    healthLabel.p_id = mgr_gui->GetAmountOfLabels();
    healthLabel.p_rect = {0, 0, 60, 20};
    healthLabel.p_color = RED;
    healthLabel.p_boundingSize = 2.0f;
    healthLabel.p_boundingColor = healthLabel.p_color * 0.8f;
    healthLabel.p_visible = false;
    healthLabel.p_updateFunction = [this](float deltaTime, Label &label)
    {
        const Enemy *enemy = this->mgr_enemy->GetHoveredEnemy();
        if (!enemy)
        {
            label.p_visible = false;
            return;
        }
        
        label.p_rect.x = enemy->p_position.x + enemy->p_sourceRect.width + Settings::g_boundingSize;
        label.p_rect.y = enemy->p_position.y;
        label.p_text = "Health: " + std::to_string(enemy->p_health);
        label.p_visible = true;
    };
    #pragma endregion
}

void EnemyHover::InitButtons()
{
    
}

void EnemyHover::InjectDependencies(EnemyManager *enemyManager, GuiManager *guiManager)
{
    mgr_enemy = enemyManager;
    mgr_gui = guiManager;
}

void EnemyHover::Init()
{
    assert(mgr_enemy != nullptr && "EnemyManager wasn't injected and its dependency");
    assert(mgr_gui != nullptr && "GuiManager wasn't injected and its dependency");
    InitLabels();
    InitButtons();
}
