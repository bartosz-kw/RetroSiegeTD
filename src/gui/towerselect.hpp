#pragma once
#include <vector>
#include "../structs/textlabel.hpp"

class TowerManager; // Forward declaration

class TowerSelect
{
private:
    std::vector<TextLabel> m_textLabels = {};
    TowerManager* mgr_tower = nullptr;

private:
    void UpdateTextPosition(TextLabel& label);
    void InitLabels();

public:
    void Update();
    void Draw() const;
    void InjectDependencies(TowerManager* towerManager);
    void Init();
};
