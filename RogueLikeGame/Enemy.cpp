#include "Enemy.h"
#include "Player.h"
#include <iostream>

#include "../Engine/GameWorld.h"
#include "../Engine/ResourceSystem.h"
#include "../Engine/RigidbodyComponent.h"
#include "../Engine/SpriteColliderComponent.h"
#include "../Engine/SpriteRendererComponent.h"
#include "../Engine/TransformComponent.h"
#include "ArmorBarComponent.h"
#include "ArmorComponent.h"
#include "AttackComponent.h"
#include "CombatSystem.h"
#include "EnemyAIComponent.h"
#include "HealthBarComponent.h"
#include "HealthComponent.h"

namespace Roguelike {
Enemy::Enemy(const EngineZ::Vector2Df& position, Player* player)
    : targetPlayer(player) {
    gameObject = EngineZ::GameWorld::Instance()->CreateGameObject("Enemy");
    auto transform = gameObject->GetComponent<EngineZ::TransformComponent>();
    transform->SetWorldPosition(position);

    // Визуальные компоненты врага
    auto renderer = gameObject->AddComponent<EngineZ::SpriteRendererComponent>();
    renderer->SetTexture(*EngineZ::ResourceSystem::Instance()->GetTextureMapElementShared("enemies", 0));
    renderer->SetPixelSize(64, 64);

    // Физические компоненты
    auto rigidbody = gameObject->AddComponent<EngineZ::RigidbodyComponent>();
    rigidbody->SetKinematic(false);
    auto collider = gameObject->AddComponent<EngineZ::SpriteColliderComponent>();
    collider->SetTrigger(false);

    // Боевые характеристики
    health = gameObject->AddComponent<HealthComponent>();
    armor = gameObject->AddComponent<ArmorComponent>();
    attack = gameObject->AddComponent<AttackComponent>();

    health->SetHealth(50);
    armor->SetArmor(3);
    attack->SetDamage(10);
    attack->SetRange(70.0f);

    // Искусственный интеллект
    ai = gameObject->AddComponent<EnemyAIComponent>();
    if (player && player->GetGameObject()) {
        ai->SetTarget(player->GetGameObject());
    }
    ai->SetMovementSpeed(120.0f);
    ai->SetAttackRange(70.0f);
    ai->SetVisionRange(250.0f);

    // Интерфейсные элементы
    auto healthBar = gameObject->AddComponent<HealthBarComponent>();
    healthBar->SetOffset(-40.0f);
    healthBar->SetSize(60.0f, 6.0f);

    auto armorBar = gameObject->AddComponent<ArmorBarComponent>();
    armorBar->SetOffset(-50.0f);
    armorBar->SetSize(60.0f, 6.0f);

    CombatSystem::Instance()->RegisterHealthComponent(health);
}

void Enemy::Update(float deltaTime) {
    // Логика обновления врага
}

bool Enemy::IsAlive() const { return health && health->IsAlive(); }


}  // namespace Roguelike