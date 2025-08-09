#pragma once
#include "Component.h"

namespace Roguelike {
class HealthComponent : public EngineZ::Component {
   public:
    HealthComponent(EngineZ::GameObject* gameObject);
    void SetHealth(int health);
    void TakeDamage(int amount);
    bool IsAlive() const;
    int GetHealth() const;

    void Update(float deltaTime) override {}
    void Render() override {}

   private:
    int currentHealth;
};
}  // namespace Roguelike
