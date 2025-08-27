#include "Player.h"

#include <cmath>
#include <iostream>

#include "../Engine/GameWorld.h"
#include "../Engine/InputComponent.h"
#include "../Engine/MovementComponent.h"
#include "../Engine/ResourceSystem.h"
#include "../Engine/RigidbodyComponent.h"
#include "../Engine/SpriteAnimationComponent.h"
#include "../Engine/SpriteColliderComponent.h"
#include "../Engine/SpriteRendererComponent.h"
#include "../Engine/TransformComponent.h"
#include "ArmorBarComponent.h"
#include "ArmorComponent.h"
#include "AttackComponent.h"
#include "CombatSystem.h"
#include "DeveloperLevel.h"
#include "Enemy.h"
#include "HealthBarComponent.h"
#include "HealthComponent.h"

namespace Roguelike {
Player::Player(const EngineZ::Vector2Df& position, DeveloperLevel* level)
    : level(level) {
    gameObject = EngineZ::GameWorld::Instance()->CreateGameObject("Player");
    auto transform = gameObject->GetComponent<EngineZ::TransformComponent>();
    transform->SetWorldPosition(position);

    // Основные компоненты игрока
    auto renderer = gameObject->AddComponent<EngineZ::SpriteRendererComponent>();
    auto texture = EngineZ::ResourceSystem::Instance()->GetTextureMapElementShared("player", 0);
    if (texture) {
        renderer->SetTexture(*texture);
    }
    renderer->SetPixelSize(64, 64);

    inputComponent = gameObject->AddComponent<EngineZ::InputComponent>();
    auto movement = gameObject->AddComponent<EngineZ::MovementComponent>();
    movement->SetSpeed(400.0f);

    // Физика и коллизии
    gameObject->AddComponent<EngineZ::RigidbodyComponent>();
    auto collider = gameObject->AddComponent<EngineZ::SpriteColliderComponent>();
    collider->SetTrigger(false);

    // Система здоровья и брони
    health = gameObject->AddComponent<HealthComponent>();
    armor = gameObject->AddComponent<ArmorComponent>();
    attackComponent = gameObject->AddComponent<PlayerAttackComponent>();

    // Начальные значения характеристик
    health->SetHealth(100);
    armor->SetArmor(5);
    attackComponent->SetDamage(15);
    attackComponent->SetRange(1650.0f);

    CombatSystem::Instance()->RegisterHealthComponent(health);

    // Интерфейсные элементы
    auto healthBar = gameObject->AddComponent<HealthBarComponent>();
    healthBar->SetOffset(-40.0f);
    healthBar->SetSize(60.0f, 6.0f);

    auto armorBar = gameObject->AddComponent<ArmorBarComponent>();
    armorBar->SetOffset(-50.0f);
    armorBar->SetSize(60.0f, 6.0f);
}

void Player::HandleInput(float deltaTime) {
    if (!inputComponent) return;

    bool attackPressed = inputComponent->IsAttackPressed();

    if (attackPressed && currentAttackCooldown <= 0) {
        Attack();
    }
}

void Player::Update(float deltaTime) {
    HandleInput(deltaTime);

    if (currentAttackCooldown > 0) {
        currentAttackCooldown -= deltaTime;
    }
}

void Player::Attack() {
    if (currentAttackCooldown > 0 || !attackComponent) {
        return;
    }

    attackComponent->Attack();
    currentAttackCooldown = attackCooldown;
}

bool Player::IsAlive() const { return health && health->IsAlive(); }

EngineZ::GameObject* Player::GetGameObject() { return gameObject; }
}  // namespace Roguelike