#pragma once
#include <vector>
#include "../structs/button.hpp"
#include "../structs/textlabel.hpp"

class TowerManager; 
class GuiManager;
class TowerSelect
{
private:
    TowerManager* mgr_tower = nullptr;
    GuiManager* mgr_gui = nullptr;
private:
    void UpdateTextPosition(TextLabel& label);
    void UpdateTextPosition(Button& label);
    void InitLabels();
    void InitButtons();

public:
    void InjectDependencies(TowerManager* towerManager,GuiManager* guiManager);
    void Init();
};
