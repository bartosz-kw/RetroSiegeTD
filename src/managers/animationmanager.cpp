#include "animationmanager.hpp"

#include <algorithm>

#include "../namespaces/basics.hpp"

void AnimationManager::Init() {
    m_animations.clear();
}

void AnimationManager::RunAnimation(
    Enemy* enemy,
    uint16_t startingFrame,
    uint16_t amountOfFrames,
    bool instantStart,
    bool autoRevert
) {
    m_animations.emplace_back(enemy, startingFrame, amountOfFrames, instantStart, autoRevert);
}

void AnimationManager::Update(const float deltaTime) {
    for (const auto& anim : m_animations) {
        auto [enemy, startingFrame, amountOfFrames, instantStart, autoRevert] = anim;
        Basics::PlayAnimation(
            deltaTime,
            *enemy,
            startingFrame,
            amountOfFrames,
            instantStart,
            autoRevert
        );
    }

    m_animations.erase(
        std::remove_if(
            m_animations.begin(),
            m_animations.end(),
            [](const auto& anim) {
                auto [enemy, startingFrame, amountOfFrames, instantStart, autoRevert] = anim;
                return !enemy->p_inSpecialAnim;
            }
        ),
        m_animations.end()
    );
}
