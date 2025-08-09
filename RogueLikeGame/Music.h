#pragma once

#include <AudioComponent.h>
#include <GameObject.h>
#include <GameWorld.h>
#include <ResourceSystem.h>

class Music {
   public:
    Music(const std::string& soundName);

   private:
    EngineZ::GameObject* gameObject;
};
