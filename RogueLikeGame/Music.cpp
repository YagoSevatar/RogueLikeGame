#include "Music.h"

Music::Music(const std::string& soundName) {
    auto gameObject =
        EngineZ::GameWorld::Instance()->CreateGameObject("Music: " + soundName);
    auto music = gameObject->AddComponent<EngineZ::AudioComponent>();
    music->SetAudio(*EngineZ::ResourceSystem::Instance()->GetSound(soundName));
    music->SetLoop(true);
    music->Play();
}