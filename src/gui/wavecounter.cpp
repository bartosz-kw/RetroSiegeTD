#include "wavecounter.hpp"
#include "../utility/debugUtil.hpp"

void WaveCounter::UpdateTextPosition(TextLabel& label)
{
    Vector2 textMeasurement = MeasureTextEx(GetFontDefault(),label.p_text.c_str(),GetFontDefault().baseSize,1.0f);
    label.p_textPosition = {label.p_rect.x + label.p_rect.width / 2.0f - textMeasurement.x / 2.0f,label.p_rect.y + label.p_rect.height / 2.0f - textMeasurement.y / 2.0f};
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
        DrawRectangleRec(label.p_rect,label.p_color);
        DrawTextEx(GetFontDefault(),label.p_text.c_str(),label.p_textPosition,label.p_fontSize,1.0f,BLACK);
    }
}

void WaveCounter::Init()
{
    TextLabel waveCountLabel = {};
    waveCountLabel.p_text = "eeeee";
    waveCountLabel.p_id = 1;
    waveCountLabel.p_fontSize = GetFontDefault().baseSize;
    waveCountLabel.p_rect = {0,0,100,20};

    m_textLabels.push_back(waveCountLabel);
}