#include "HealthComponent.h"

#include <iostream>

namespace Roguelike {
HealthComponent::HealthComponent(EngineZ::GameObject* gameObject)
    : EngineZ::Component(gameObject) {}

void HealthComponent::SetHealth(int health) {
    currentHealth = health;
    isDead = (health <= 0);
}

void HealthComponent::TakeDamage(int amount) {
    if (isDead) return;

    currentHealth = std::max(0, currentHealth - amount);
    if (currentHealth <= 0) {
        isDead = true;
        std::cout << "Entity died!" << std::endl;
    }
}

bool HealthComponent::IsAlive() const { return !isDead; }
bool HealthComponent::IsDead() const { return isDead; }
int HealthComponent::GetHealth() const { return currentHealth; }
}  // namespace Roguelike