#pragma once
#include <vector>
#include <tuple>
#include "../structs/enemy.hpp"

class AnimationManager
{
private:
    std::vector<std::tuple<Enemy*, uint16_t, uint16_t>> m_animations = {};

public:
    AnimationManager() = default;

    void RunAnimation(Enemy* enemy, uint16_t startingFrame, uint16_t amountOfFrames);
    void Update(const float deltaTime);
    void Init();
};
