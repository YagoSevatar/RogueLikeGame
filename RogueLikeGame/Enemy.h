#pragma once
#include <Vector.h>

#include "HealthComponent.h"
namespace Roguelike {
class Enemy {
   public:
    Enemy(const EngineZ::Vector2Df& position);
    EngineZ::GameObject* GetGameObject() const;

   private:
    EngineZ::GameObject* gameObject;
};
}  // namespace Roguelike
