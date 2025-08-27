#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/AudioComponent.h"
#include <GameWorld.h>
#include <ResourceSystem.h>

class Music {
   public:
    Music(const std::string& soundName);

   private:
    EngineZ::GameObject* gameObject;
};