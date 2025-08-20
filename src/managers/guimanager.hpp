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
    void UpdateImagePosition(Button &button);
    void UpdatePress(const float deltaTime,Button &button);
    void UpdateLabel(const float deltaTime,TextLabel &label,const bool gameStarted);
    void UpdateButton(const float deltaTime,Button &button,const bool gameStarted);
    void DrawButton(const Button &button,const bool gameStarted) const;
    void DrawLabel(const TextLabel &label,const bool gameStarted) const;

public:
    
    const size_t GetAmountOfLabels() const;
    const size_t GetAmountOfButtons() const;
    void ReserveButton(const size_t count);
    void ReserveLabel(const size_t count);
    Button& AddButton(const Button &button);
    TextLabel& AddLabel(const TextLabel &label);
    void RemoveButton(const int id);
    void RemoveLabel(const int id);
    void Update(const float deltaTime,const bool gameStarted);
    void Draw(const bool gameStarted) const;
    void Init();
    
};
