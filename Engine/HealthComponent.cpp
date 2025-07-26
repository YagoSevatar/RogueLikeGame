#include "pch.h"
#include "HealthComponent.h"
#include "Logger.h"

namespace EngineZ
{
    HealthComponent::HealthComponent(GameObject* gameObject, int maxHealth, int armor)
        : Component(gameObject), maxHealth(maxHealth), currentHealth(maxHealth), armor(armor)
    {
        LOG_INFO("HealthComponent created for " + gameObject->GetName() +
            " with " + std::to_string(maxHealth) + " health and " +
            std::to_string(armor) + " armor");
    }

    void HealthComponent::TakeDamage(int amount)
    {
        if (amount <= 0)
        {
            LOG_WARN("Attempt to deal non-positive damage: " + std::to_string(amount));
            return;
        }

        int damageAfterArmor = std::max(1, amount - armor);
        currentHealth -= damageAfterArmor;

        LOG_INFO(gameObject->GetName() + " took " + std::to_string(damageAfterArmor) +
            " damage (after armor). Remaining health: " + std::to_string(currentHealth));

        if (IsDead())
        {
            LOG_INFO(gameObject->GetName() + " has been defeated");
        }
    }

    void HealthComponent::Heal(int amount)
    {
        if (amount <= 0)
        {
            LOG_WARN("Attempt to heal with non-positive amount: " + std::to_string(amount));
            return;
        }

        currentHealth = std::min(maxHealth, currentHealth + amount);
        LOG_INFO(gameObject->GetName() + " healed for " + std::to_string(amount) +
            ". Current health: " + std::to_string(currentHealth));
    }

    void HealthComponent::SetArmor(int newArmor)
    {
        if (newArmor < 0)
        {
            LOG_WARN("Attempt to set negative armor: " + std::to_string(newArmor));
            armor = 0;
            return;
        }

        armor = newArmor;
        LOG_INFO(gameObject->GetName() + " armor set to " + std::to_string(armor));
    }
}