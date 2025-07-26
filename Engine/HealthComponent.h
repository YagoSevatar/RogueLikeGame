#pragma once
#include "Component.h"
#include "Logger.h"
#include "GameObject.h" 

namespace EngineZ
{
    class HealthComponent : public Component
    {
    public:
        HealthComponent(GameObject* gameObject, int maxHealth, int armor = 0);

        void TakeDamage(int amount);
        void Heal(int amount);
        void SetArmor(int newArmor);

        int GetCurrentHealth() const { return currentHealth; }
        int GetMaxHealth() const { return maxHealth; }
        int GetArmor() const { return armor; }
        bool IsDead() const { return currentHealth <= 0; }

        void Update(float deltaTime) override {}
        void Render() override {}

    private:
        int maxHealth;
        int currentHealth;
        int armor;
    };
}