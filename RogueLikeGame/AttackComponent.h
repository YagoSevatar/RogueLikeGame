#pragma once
#include "../Engine/Component.h"

namespace Roguelike {
class AttackComponent : public EngineZ::Component {
   public:
    AttackComponent(EngineZ::GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    void SetDamage(int damage);
    int GetDamage() const { return damage; }
    float GetRange() const { return attackRange; }
    void SetRange(float range) { attackRange = range; }

   private:
    int damage = 10;
    float attackRange = 100.0f;
};
}  // namespace Roguelike