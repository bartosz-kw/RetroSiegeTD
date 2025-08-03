#include "wavecounter.hpp"
#include "../utility/debugUtil.hpp"
#include "../managers/wavemanager.hpp"
#include <cassert>

void WaveCounter::UpdateTextPosition(TextLabel& label)
{
    Vector2 textMeasurement = MeasureTextEx(GetFontDefault(),label.p_text.c_str(),GetFontDefault().baseSize,1.0f);
    label.p_textPosition = {label.p_rect.x + label.p_rect.width / 2.0f - textMeasurement.x / 2.0f,label.p_rect.y + label.p_rect.height / 2.0f - textMeasurement.y / 2.0f};
}

void WaveCounter::InitLabels()
{
    m_textLabels.emplace_back(TextLabel{});
    TextLabel& waveCountLabel = m_textLabels.back();
    waveCountLabel.p_text = "Wave:";
    waveCountLabel.p_id = 1;
    waveCountLabel.p_fontSize = GetFontDefault().baseSize;
    waveCountLabel.p_rect = {0,4,105,20};
    waveCountLabel.p_color = GREEN;
    waveCountLabel.p_updateFunction = [&waveCountLabel,this]()
    {
        EnemyWave* currentWave = mgr_wave->GetSmallestIdWave();
        if (!currentWave)
        {
            waveCountLabel.p_text = "Victory!";
            return;
        }
        
        std::string text = "Wave: " + std::to_string(currentWave->p_id);
        waveCountLabel.p_text = text;
    };
}


void WaveCounter::Update()
{
    for (auto &label : m_textLabels)
    {
        UpdateTextPosition(label);
        label.p_updateFunction();
    }
    
}

void WaveCounter::Draw() const
{
    for (auto &label : m_textLabels)
    {
        DrawRectangleRounded(label.p_rect,10.0f,4.0f,label.p_color);
        //DrawRectangleRec(label.p_rect,label.p_color);
        DrawTextEx(GetFontDefault(),label.p_text.c_str(),label.p_textPosition,label.p_fontSize,1.0f,BLACK);
    }
}

void WaveCounter::InjectDependencies(WaveManager* waveManager)
{
    mgr_wave = waveManager;
}

void WaveCounter::Init()
{
    assert(mgr_wave != nullptr && "WaveManager wasn't injected and its dependency");
    InitLabels();
}
