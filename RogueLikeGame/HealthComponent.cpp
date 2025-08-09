#include "HealthComponent.h"

#include "GameWorld.h"

namespace Roguelike {
HealthComponent::HealthComponent(EngineZ::GameObject* gameObject)
    : Component(gameObject), currentHealth(100) {}

void HealthComponent::SetHealth(int health) { currentHealth = health; }

void HealthComponent::TakeDamage(int amount) {
    currentHealth = std::max(0, currentHealth - amount);
    if (!IsAlive()) {
        EngineZ::GameWorld::Instance()->DestroyGameObject(gameObject);
    }
}

bool HealthComponent::IsAlive() const { return currentHealth > 0; }

int HealthComponent::GetHealth() const { return currentHealth; }
}  // namespace Roguelike
