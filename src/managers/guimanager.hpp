#pragma once
#include <vector>
#include <functional>
#include "../structs/textlabel.hpp"
#include "../structs/button.hpp"

class GuiManager
{
private:

    bool m_gameState = false;
    std::vector<TextLabel> m_labels;
    std::vector<Button> m_buttons;

private:

    void UpdateTextPosition(TextLabel &label);
    void UpdateTextPosition(Button &button);
    void UpdateImagePosition(Button &button);
    void UpdatePress(const float deltaTime,Button &button);
    void UpdateLabel(const float deltaTime,TextLabel &label);
    void UpdateButton(const float deltaTime,Button &button);
    void DrawButton(const Button &button) const;
    void DrawLabel(const TextLabel &label) const;
    const bool IsElementUsed(const Button &button) const;
    const bool IsElementUsed(const TextLabel &label) const;

public:
    
    const size_t GetAmountOfLabels() const;
    const size_t GetAmountOfButtons() const;
    void ReserveButton(const size_t count);
    void ReserveLabel(const size_t count);
    Button& AddButton(const Button &button);
    TextLabel& AddLabel(const TextLabel &label);
    void RemoveButton(const int id);
    void RemoveLabel(const int id);
    void SyncGameState(const bool gameState);
    void Update(const float deltaTime);
    void Draw() const;
    void Init();
    
};
