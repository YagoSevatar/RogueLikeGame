#include "CombatSystem.h"

#include <cmath>

#include "TransformComponent.h"

namespace Roguelike {
CombatSystem* CombatSystem::Instance() {
    static CombatSystem instance;
    return &instance;
}

void CombatSystem::RegisterHealthComponent(HealthComponent* healthComponent) {
    healthComponents.push_back(healthComponent);
}

void CombatSystem::Update() {
    const float DAMAGE_DISTANCE = 100.0f;
    const int DAMAGE_AMOUNT = 5;

    for (size_t i = 0; i < healthComponents.size(); ++i) {
        auto transformI = healthComponents[i]
                              ->GetGameObject()
                              ->GetComponent<EngineZ::TransformComponent>();
        auto posI = transformI->GetWorldPosition();

        for (size_t j = i + 1; j < healthComponents.size(); ++j) {
            auto transformJ = healthComponents[j]
                                  ->GetGameObject()
                                  ->GetComponent<EngineZ::TransformComponent>();
            auto posJ = transformJ->GetWorldPosition();

            // Проверяем расстояние между объектами
            float dx = posI.x - posJ.x;
            float dy = posI.y - posJ.y;
            float distance = sqrtf(dx * dx + dy * dy);

            if (distance < DAMAGE_DISTANCE) {
                healthComponents[i]->TakeDamage(DAMAGE_AMOUNT);
                healthComponents[j]->TakeDamage(DAMAGE_AMOUNT);
            }
        }
    }
}
}  // namespace Roguelike
