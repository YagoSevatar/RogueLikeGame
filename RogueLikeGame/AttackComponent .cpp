#include <cmath>
#include <iostream>

#include "../Engine/GameObject.h"
#include "../Engine/TransformComponent.h"
#include "ArmorComponent.h"
#include "AttackComponent.h"
#include "HealthComponent.h"

namespace Roguelike {
AttackComponent::AttackComponent(EngineZ::GameObject* gameObject)
    : EngineZ::Component(gameObject) {}

void AttackComponent::Update(float deltaTime) {
    if (currentCooldown > 0) {
        currentCooldown -= deltaTime;
    }
}

void AttackComponent::Attack() {
    if (!CanAttack() || !target || !IsInRange()) return;

    auto targetHealth = target->GetComponent<HealthComponent>();
    auto targetArmor = target->GetComponent<ArmorComponent>();

    if (targetHealth) {
        int finalDamage = damage;

        if (targetArmor) {
            finalDamage = targetArmor->ReduceDamage(finalDamage);
        }

        targetHealth->TakeDamage(finalDamage);
        std::cout << "Attacked for " << finalDamage << " damage!" << std::endl;

        currentCooldown = cooldown;
    }
}

void AttackComponent::SetTarget(EngineZ::GameObject* target) {
    this->target = target;
}

void AttackComponent::SetDamage(int damage) { this->damage = damage; }

void AttackComponent::SetRange(float range) { this->attackRange = range; }

bool AttackComponent::IsInRange() const {
    if (!target || !gameObject) return false;

    auto myTransform = gameObject->GetComponent<EngineZ::TransformComponent>();
    auto targetTransform = target->GetComponent<EngineZ::TransformComponent>();

    if (!myTransform || !targetTransform) return false;

    auto myPos = myTransform->GetWorldPosition();
    auto targetPos = targetTransform->GetWorldPosition();

    float dx = myPos.x - targetPos.x;
    float dy = myPos.y - targetPos.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    return distance <= attackRange;
}

bool AttackComponent::CanAttack() const { return currentCooldown <= 0; }
}  // namespace Roguelike