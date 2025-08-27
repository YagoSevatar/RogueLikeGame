#pragma once

#include <../Engine/GameWorld.h>
#include <../Engine/ResourceSystem.h>

#include "../Engine/GameObject.h"

namespace Roguelike {
class Wall {
   public:
    Wall(const EngineZ::Vector2Df position, int textureMapIndex);
    EngineZ::GameObject* GetGameObject() const { return gameObject; }

   private:
    EngineZ::GameObject* gameObject;
};
}  // namespace Roguelike
