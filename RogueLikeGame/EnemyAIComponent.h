#pragma once
#include "../Engine/Component.h"

namespace Roguelike {
class EnemyAIComponent : public EngineZ::Component {
   public:
    EnemyAIComponent(EngineZ::GameObject* gameObject);
    void Update(float deltaTime) override;
    void Render() override {}

    void SetTarget(EngineZ::GameObject* target);
    void SetMovementSpeed(float speed);
    void SetAttackRange(float range);
    void SetVisionRange(float range);
    bool CanAttack() const { return attackCooldown <= 0; }
    void SetAttackCooldown(float cooldown) { this->attackCooldown = cooldown; }
   private:
    EngineZ::GameObject* target = nullptr;
    float movementSpeed = 150.0f;
    float attackRange = 100.0f;
    float visionRange = 300.0f;
    float attackCooldown = 0.0f;
    float attackCooldownTime = 1.0f;
};
}  // namespace Roguelike