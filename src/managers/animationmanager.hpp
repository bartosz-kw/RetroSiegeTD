#pragma once
#include <tuple>
#include <vector>

#include "../structs/enemy.hpp"

class AnimationManager {
private:
    std::vector<std::tuple<Enemy*, uint16_t, uint16_t, bool, bool>> m_animations = {};

public:
    AnimationManager() = default;

    void RunAnimation(
        Enemy* enemy,
        uint16_t startingFrame,
        uint16_t amountOfFrames,
        bool instantStart,
        bool autoRevert
    );
    void Update(const float deltaTime);
    void Init();
};
