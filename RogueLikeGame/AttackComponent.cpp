#include "AttackComponent.h"

namespace Roguelike {
AttackComponent::AttackComponent(EngineZ::GameObject* gameObject)
    : EngineZ::Component(gameObject) {}

void AttackComponent::Update(float deltaTime) {

}

void AttackComponent::Render() {

}

void AttackComponent::SetDamage(int damage) { this->damage = damage; }
}  // namespace Roguelike