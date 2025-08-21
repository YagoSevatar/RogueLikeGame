#include "EnemyAIComponent.h"

#include <cmath>
#include <iostream>

#include "../Engine/GameObject.h"
#include "../Engine/RigidbodyComponent.h"
#include "../Engine/TransformComponent.h"
#include "AttackComponent.h"

namespace Roguelike {
EnemyAIComponent::EnemyAIComponent(EngineZ::GameObject* gameObject)
    : EngineZ::Component(gameObject) {}

void EnemyAIComponent::Update(float deltaTime) {
    if (!target) return;

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

    // Нормализуем направление
    if (distance > 0) {
        dx /= distance;
        dy /= distance;
    }

    // Если в зоне атаки - атакуем
    if (distance <= attackRange && attack && attack->CanAttack()) {
        rigidbody->SetLinearVelocity({0, 0});
        attack->SetTarget(target);
        attack->Attack();
    }
    // Если в зоне преследования - движемся к цели
    else if (distance <= visionRange) {
        // Плавное движение
        rigidbody->SetLinearVelocity(
            {dx * movementSpeed * (distance / visionRange),
             dy * movementSpeed * (distance / visionRange)});
    }
    // Если цель вне зоны видимости - патрулируем или стоим
    else {
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