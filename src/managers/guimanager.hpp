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

public:
    void Init();

    void ReserveButton(size_t count);
    void ReserveLabel(size_t count);
    Button& AddButton(const Button &button);
    TextLabel& AddLabel(const TextLabel &label);
    void RemoveButton(int id);
    void RemoveLabel(int id);

    void Update();
    void Draw() const;
};
