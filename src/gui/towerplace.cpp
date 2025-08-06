#include "towerplace.hpp"
#include "../namespaces/settings.hpp"
#include "../utility/debugUtil.hpp"
#include "../managers/towermanager.hpp"
#include "../managers/guimanager.hpp"
#include <format>
#include <cassert>

void TowerPlace::InitLabels()
{
    PrintDebug("eh");
    TextLabel& headerLabel = mgr_gui->AddLabel(TextLabel{});
    headerLabel.p_rect = {static_cast<float>(Settings::g_boundingSize + 270.0f),0.0f,static_cast<float>(Settings::g_boundingSize),20};
    headerLabel.p_id = mgr_gui->GetAmountOfLabels();
    headerLabel.p_text = "Towers: ";
}

void TowerPlace::InitButtons()
{
    // TODO: Initialize buttons when needed
}

void TowerPlace::InjectDependencies(TowerManager* towerManager,GuiManager* guiManager)
{
    mgr_tower = towerManager;
    mgr_gui = guiManager;
}

void TowerPlace::Init()
{
    assert(mgr_tower != nullptr && "TowerManager wasn't injected and its dependency");
    assert(mgr_gui != nullptr && "GuiManager wasn't injected and its dependency");
    InitLabels();
    InitButtons();
}
