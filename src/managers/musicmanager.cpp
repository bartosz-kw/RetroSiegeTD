#include "musicmanager.hpp"
#include "../namespaces/music.hpp"

void MusicManager::Init()
{
    GameMusic::InitAudio();
    GameMusic::LoadSounds();
    GameMusic::LoadMusic();
}

void MusicManager::Update()
{
    GameMusic::UpdateMusic();
}
