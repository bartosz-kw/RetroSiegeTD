#include "audiomanager.hpp"
#include "../namespaces/music.hpp"

void AudioManager::Init()
{
    GameMusic::InitAudio();
    GameMusic::LoadSounds();
    GameMusic::LoadMusic();
}

void AudioManager::Update()
{
    GameMusic::UpdateMusic();
}
