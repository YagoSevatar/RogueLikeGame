#pragma once
#include "../Engine/GameObject.h"

namespace Roguelike {
class Player;
class HealthComponent;
class ArmorComponent;
class AttackComponent;
class EnemyAIComponent;

class Enemy {
   public:
    Enemy(const EngineZ::Vector2Df& position, Player* player);
    EngineZ::GameObject* GetGameObject() const { return gameObject; }
    void Update(float deltaTime);
    bool IsAlive() const;

   private:
    EngineZ::GameObject* gameObject;
    Player* targetPlayer;
    HealthComponent* health;
    ArmorComponent* armor;
    AttackComponent* attack;
    EnemyAIComponent* ai;
};
}  // namespace Roguelike