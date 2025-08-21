#include "CombatSystem.h"

#include "HealthComponent.h"

namespace Roguelike {
CombatSystem* CombatSystem::Instance() {
    static CombatSystem instance;
    return &instance;
}

void CombatSystem::Update() {

}

void CombatSystem::RegisterHealthComponent(HealthComponent* healthComponent) {
    healthComponents.push_back(healthComponent);
}

void CombatSystem::UnregisterHealthComponent(HealthComponent* healthComponent) {
    healthComponents.erase(std::remove(healthComponents.begin(),
                                       healthComponents.end(), healthComponent),
                           healthComponents.end());
}
}  // namespace Roguelike