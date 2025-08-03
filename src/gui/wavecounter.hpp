#include "../structs/textlabel.hpp"

class WaveManager; // Forward declaration

class WaveCounter
{
private:
    std::vector<TextLabel> m_textLabels = {};
    WaveManager* mgr_wave = nullptr;
    
private:
    void UpdateTextPosition(TextLabel& label);
    void InitLabels();
    
public:
    void Update();
    void Draw() const;
    void InjectDependencies(WaveManager* waveManager);
    void Init();
};
