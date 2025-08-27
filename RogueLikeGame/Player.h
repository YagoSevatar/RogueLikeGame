#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/InputComponent.h"
#include "ArmorComponent.h"
#include "HealthComponent.h"
#include "PlayerAttackComponent.h"

namespace Roguelike {
class DeveloperLevel;
class HealthComponent;
class ArmorComponent;
class PlayerAttackComponent;

class Player {
   public:
    Player(const EngineZ::Vector2Df& position, DeveloperLevel* level);
    EngineZ::GameObject* GetGameObject();
    void Attack();
    void Update(float deltaTime);
    bool IsAlive() const;

   private:
    void HandleInput(float deltaTime);

    EngineZ::GameObject* gameObject;
    DeveloperLevel* level;
    EngineZ::InputComponent* inputComponent;
    HealthComponent* health;
    ArmorComponent* armor;
    PlayerAttackComponent* attackComponent;

    float attackCooldown = 0.5f;
    float currentAttackCooldown = 0.0f;
};
}  // namespace Roguelike