#pragma once
#include <vector>
#include "../structs/button.hpp"
#include "../structs/textlabel.hpp"

class TowerManager; 
class TowerSelect
{
private:
    std::vector<Button> m_buttons = {};
    std::vector<TextLabel> m_textLabels = {};
    TowerManager* mgr_tower = nullptr;

private:
    void UpdateTextPosition(TextLabel& label);
    void UpdateTextPosition(Button& label);
    void InitLabels();
    void InitButtons();

public:
    void Update();
    void Draw() const;
    void InjectDependencies(TowerManager* towerManager);
    void Init();
};
