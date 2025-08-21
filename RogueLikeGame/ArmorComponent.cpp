#include "ArmorComponent.h"

namespace Roguelike {
ArmorComponent::ArmorComponent(EngineZ::GameObject* gameObject)
    : EngineZ::Component(gameObject) {}

void ArmorComponent::SetArmor(int armor) { armorValue = armor; }

int ArmorComponent::GetArmor() const { return armorValue; }

int ArmorComponent::ReduceDamage(int damage) {
    if (armorValue <= 0) return damage;

    int reducedDamage = damage - armorValue;
    if (reducedDamage < 0) reducedDamage = 0;

    return reducedDamage;
}
}  // namespace Roguelike