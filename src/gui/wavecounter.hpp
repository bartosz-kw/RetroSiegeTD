#include "../structs/textlabel.hpp"

class WaveCounter
{
private:
    std::vector<TextLabel> m_textLabels = {};
private:
    void UpdateTextPosition(TextLabel& label);
public:
    void Update();
    void Draw() const;
    void Init();
};
