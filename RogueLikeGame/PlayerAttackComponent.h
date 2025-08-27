#pragma once
#include "../Engine/Component.h"

namespace Roguelike {
class PlayerAttackComponent : public EngineZ::Component {
   public:
    PlayerAttackComponent(EngineZ::GameObject* gameObject);
    void Update(float deltaTime) override;
    void Render() override {}

    void Attack();
    bool CanAttack() const { return currentCooldown <= 0; }
    void SetCooldown(float cooldown) { attackCooldown = cooldown; }
    void SetDamage(int newDamage) { damage = newDamage; }
    void SetRange(float newRange) { attackRange = newRange; }
    int GetDamage() const { return damage; }
    float GetRange() const { return attackRange; }

   private:
    float attackCooldown = 0.5f;
    float currentCooldown = 0.0f;
    float attackRange = 150.0f;
    int damage = 15;
};
}  // namespace Roguelike