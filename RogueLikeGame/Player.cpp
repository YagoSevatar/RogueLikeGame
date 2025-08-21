#include "Player.h"

#include <iostream>

#include "../Engine/GameWorld.h"
#include "../Engine/InputComponent.h"
#include "../Engine/MovementComponent.h"
#include "../Engine/ResourceSystem.h"
#include "../Engine/RigidbodyComponent.h"
#include "../Engine/SpriteAnimationComponent.h"
#include "../Engine/SpriteColliderComponent.h"
#include "../Engine/SpriteRendererComponent.h"
#include "ArmorComponent.h"
#include "AttackComponent.h"
#include "CombatSystem.h"
#include "HealthComponent.h"

namespace Roguelike {
Player::Player(const EngineZ::Vector2Df& position) {
    gameObject = EngineZ::GameWorld::Instance()->CreateGameObject("Player");
    auto transform = gameObject->GetComponent<EngineZ::TransformComponent>();
    transform->SetWorldPosition(position);

    // Компоненты рендеринга
    auto renderer =
        gameObject->AddComponent<EngineZ::SpriteRendererComponent>();
    auto texture =
        EngineZ::ResourceSystem::Instance()->GetTextureMapElementShared(
            "player", 0);
    if (texture) {
        renderer->SetTexture(*texture);
    }
    renderer->SetPixelSize(64, 64);

    // Анимации
    auto animationComponent =
        gameObject->AddComponent<EngineZ::SpriteAnimationComponent>();

    EngineZ::Animation idleAnimation;
    idleAnimation.textureMapName = "player";
    idleAnimation.frameIDs = {0};
    idleAnimation.time = 0.8f;
    idleAnimation.isRightDirected = false;
    idleAnimation.priority = 0;
    idleAnimation.isLoop = true;
    animationComponent->AddAnimation("Idle", idleAnimation, true);

    EngineZ::Animation walkAnimation;
    walkAnimation.textureMapName = "player";
    walkAnimation.frameIDs = {0};
    walkAnimation.time = 1.0f;
    walkAnimation.isRightDirected = false;
    walkAnimation.priority = 0;
    walkAnimation.isLoop = true;
    animationComponent->AddAnimation("Walk", walkAnimation);

    // Компоненты управления
    gameObject->AddComponent<EngineZ::InputComponent>();
    auto movement = gameObject->AddComponent<EngineZ::MovementComponent>();
    movement->SetSpeed(400.0f);

    // Физические компоненты
    gameObject->AddComponent<EngineZ::RigidbodyComponent>();
    auto collider =
        gameObject->AddComponent<EngineZ::SpriteColliderComponent>();
    collider->SetTrigger(false);

    // Компоненты боя
    health = gameObject->AddComponent<HealthComponent>();
    armor = gameObject->AddComponent<ArmorComponent>();
    attack = gameObject->AddComponent<AttackComponent>();

    armor->SetArmor(5);
    attack->SetDamage(15);
    attack->SetRange(80.0f);

    // Регистрируем здоровье в системе боя
    CombatSystem::Instance()->RegisterHealthComponent(health);
}

void Player::Attack() {
    if (attack) {
        attack->Attack();
    }
}

void Player::Update(float deltaTime) {
}

bool Player::IsAlive() const { return health && health->IsAlive(); }
}  // namespace Roguelike