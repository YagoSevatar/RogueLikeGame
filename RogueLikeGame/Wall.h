#pragma once

#include <GameWorld.h>
#include <ResourceSystem.h>

#include "GameObject.h"

namespace Roguelike {
class Wall {
   public:
    Wall(const EngineZ::Vector2Df position, int textureMapIndex);

   private:
    EngineZ::GameObject* gameObject;
};
}  // namespace Roguelike
