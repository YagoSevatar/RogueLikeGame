#include "PlayerAttackComponent.h"

#include <cmath>
#include <iostream>

#include "../Engine/GameWorld.h"
#include "../Engine/TransformComponent.h"
#include "ArmorComponent.h"
#include "DeveloperLevel.h"  
#include "Enemy.h"         
#include "HealthComponent.h"

namespace Roguelike {
PlayerAttackComponent::PlayerAttackComponent(EngineZ::GameObject* gameObject)
    : EngineZ::Component(gameObject) {}

void PlayerAttackComponent::Update(float deltaTime) {
    if (currentCooldown > 0) {
        currentCooldown -= deltaTime;
    }
}

void PlayerAttackComponent::Attack() {
    if (!CanAttack()) return;

    auto transform = gameObject->GetComponent<EngineZ::TransformComponent>();
    if (!transform) return;

    auto playerPos = transform->GetWorldPosition();
    bool hit = false;

    // Поиск всех врагов в радиусе атаки
    auto allObjects = EngineZ::GameWorld::Instance()->GetAllGameObjects();
    for (auto obj : allObjects) {
        if (!obj || obj->GetName().find("Enemy") == std::string::npos) continue;

        auto enemyTransform = obj->GetComponent<EngineZ::TransformComponent>();
        if (!enemyTransform) continue;

        auto enemyPos = enemyTransform->GetWorldPosition();
        float dx = enemyPos.x - playerPos.x;
        float dy = enemyPos.y - playerPos.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= attackRange) {
            auto healthComp = obj->GetComponent<HealthComponent>();
            auto armorComp = obj->GetComponent<ArmorComponent>();

            if (healthComp) {
                int finalDamage = damage;
                if (armorComp) {
                    finalDamage = armorComp->ReduceDamage(finalDamage);
                }
                healthComp->TakeDamage(finalDamage);
                hit = true;
            }
        }
    }

    if (hit) {
        currentCooldown = attackCooldown;
    }
}
}  // namespace Roguelike