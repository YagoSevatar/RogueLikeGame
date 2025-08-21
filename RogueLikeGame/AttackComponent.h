#pragma once
#include "../Engine/Component.h"

namespace Roguelike {
class AttackComponent : public EngineZ::Component {
   public:
    AttackComponent(EngineZ::GameObject* gameObject);
    void Update(float deltaTime) override;
    void Render() override {}

    void Attack();
    void SetTarget(EngineZ::GameObject* target);
    void SetDamage(int damage);
    void SetRange(float range);
    bool IsInRange() const;
    bool CanAttack() const;

   private:
    EngineZ::GameObject* target = nullptr;
    int damage = 10;
    float attackRange = 100.0f;
    float cooldown = 1.0f;
    float currentCooldown = 0.0f;
};
}  // namespace Roguelike