#pragma once
#include "../Engine/Component.h"

namespace Roguelike {
class HealthComponent : public EngineZ::Component {
   public:
    HealthComponent(EngineZ::GameObject* gameObject);
    void SetHealth(int health);
    void TakeDamage(int amount);
    bool IsAlive() const;
    bool IsDead() const;
    int GetHealth() const;
    int GetMaxHealth() const { return maxHealth; }
    void Update(float deltaTime) override;
    void Render() override;

   private:
    int currentHealth = 100;
    int maxHealth = 100;
    bool isDead = false;
};
}  // namespace Roguelike