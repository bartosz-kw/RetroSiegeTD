#include "../structs/textlabel.hpp"

class WaveCounter
{
private:
    std::vector<TextLabel> m_textLabels = {};

public:
    void Update();
    void Draw() const;
    void Init();
};
