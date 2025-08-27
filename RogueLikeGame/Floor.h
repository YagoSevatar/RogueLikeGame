#pragma once
#include <../Engine/GameWorld.h>
#include <../Engine/ResourceSystem.h>
#include <../Engine/SpriteRendererComponent.h>

#include "../Engine/GameObject.h"

namespace Roguelike {
class Floor {
   public:
    Floor(const EngineZ::Vector2Df& position, int textureMapIndex,
          const sf::Color& color = sf::Color::White);

   private:
    EngineZ::GameObject* gameObject;
};
}  // namespace Roguelike