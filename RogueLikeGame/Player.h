#pragma once
#include "../Engine/GameObject.h"

namespace Roguelike {
class HealthComponent;
class ArmorComponent;
class AttackComponent;

class Player {
   public:
    Player(const EngineZ::Vector2Df& position);
    EngineZ::GameObject* GetGameObject() { return gameObject; }
    void Attack();
    void Update(float deltaTime);
    bool IsAlive() const;

   private:
    EngineZ::GameObject* gameObject;
    HealthComponent* health;
    ArmorComponent* armor;
    AttackComponent* attack;
};
}  // namespace Roguelike