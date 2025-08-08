#pragma once
#include <vector>
#include <functional>
#include "../structs/textlabel.hpp"
#include "../structs/button.hpp"

class GuiManager
{
private:

    std::vector<TextLabel> m_labels;
    std::vector<Button> m_buttons;

private:

    void UpdateTextPosition(TextLabel &label);
    void UpdateTextPosition(Button &button);
    void UpdatePress(float deltaTime,Button &button);
    void UpdateLabel(float deltaTime,TextLabel &label);
    void UpdateButton(float deltaTime,Button &button);
    void DrawButton(const Button &button) const;
    void DrawLabel(const TextLabel &label) const;

public:
    
    size_t GetAmountOfLabels() const;
    size_t GetAmountOfButtons() const;
    void ReserveButton(size_t count);
    void ReserveLabel(size_t count);
    Button& AddButton(const Button &button);
    TextLabel& AddLabel(const TextLabel &label);
    void RemoveButton(int id);
    void RemoveLabel(int id);
    void Update(float deltaTime);
    void Draw() const;
    void Init();
    
};
