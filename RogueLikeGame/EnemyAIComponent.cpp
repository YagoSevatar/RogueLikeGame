#include "EnemyAIComponent.h"

#include <cmath>
#include <iostream>

#include "../Engine/GameObject.h"
#include "../Engine/RigidbodyComponent.h"
#include "../Engine/TransformComponent.h"
#include "ArmorComponent.h"
#include "AttackComponent.h"
#include "HealthComponent.h"

namespace Roguelike {
EnemyAIComponent::EnemyAIComponent(EngineZ::GameObject* gameObject)
    : EngineZ::Component(gameObject) {}

void EnemyAIComponent::Update(float deltaTime) {
    if (!target) return;

    if (attackCooldown > 0) {
        attackCooldown -= deltaTime;
    }

    auto myTransform = gameObject->GetComponent<EngineZ::TransformComponent>();
    auto targetTransform = target->GetComponent<EngineZ::TransformComponent>();
    auto rigidbody = gameObject->GetComponent<EngineZ::RigidbodyComponent>();
    auto attack = gameObject->GetComponent<AttackComponent>();

    if (!myTransform || !targetTransform || !rigidbody) return;

    auto myPos = myTransform->GetWorldPosition();
    auto targetPos = targetTransform->GetWorldPosition();

    float dx = targetPos.x - myPos.x;
    float dy = targetPos.y - myPos.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    // Преследование игрока
    if (distance <= visionRange) {
        if (distance > 0) {
            dx /= distance;
            dy /= distance;
        }

        // Атака при близком расстоянии
        if (distance <= attackRange && attack && attackCooldown <= 0) {
            rigidbody->SetLinearVelocity({0, 0});
            auto targetHealth = target->GetComponent<HealthComponent>();
            auto targetArmor = target->GetComponent<ArmorComponent>();

            if (targetHealth) {
                int finalDamage = attack->GetDamage();
                if (targetArmor) {
                    finalDamage = targetArmor->ReduceDamage(finalDamage);
                }
                targetHealth->TakeDamage(finalDamage);
                attackCooldown = attackCooldownTime;
            }
        } else {
            // Движение к игроку
            rigidbody->SetLinearVelocity(
                {dx * movementSpeed * (distance / visionRange),
                 dy * movementSpeed * (distance / visionRange)});
        }
    } else {
        rigidbody->SetLinearVelocity({0, 0});
    }
}

void EnemyAIComponent::SetTarget(EngineZ::GameObject* target) {
    this->target = target;
}

void EnemyAIComponent::SetMovementSpeed(float speed) {
    this->movementSpeed = speed;
}

void EnemyAIComponent::SetAttackRange(float range) {
    this->attackRange = range;
}

void EnemyAIComponent::SetVisionRange(float range) {
    this->visionRange = range;
}
}  // namespace Roguelike