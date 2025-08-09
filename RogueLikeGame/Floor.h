#pragma once

#include <GameWorld.h>
#include <ResourceSystem.h>
#include <SpriteRendererComponent.h>

#include "GameObject.h"

namespace Roguelike {
class Floor {
   public:
    Floor(const EngineZ::Vector2Df& position, int textureMapIndex);

   private:
    EngineZ::GameObject* gameObject;
};
}  // namespace Roguelike
