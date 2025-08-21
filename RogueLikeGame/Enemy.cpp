#include "Enemy.h"

#include "../Engine/GameWorld.h"
#include "../Engine/ResourceSystem.h"
#include "../Engine/RigidbodyComponent.h"
#include "../Engine/SpriteColliderComponent.h"
#include "../Engine/SpriteRendererComponent.h"
#include "ArmorComponent.h"
#include "AttackComponent.h"
#include "CombatSystem.h"
#include "EnemyAIComponent.h"
#include "HealthComponent.h"
#include "Player.h"

namespace Roguelike {
Enemy::Enemy(const EngineZ::Vector2Df& position, Player* player)
    : targetPlayer(player) {
    gameObject = EngineZ::GameWorld::Instance()->CreateGameObject("Enemy");
    auto transform = gameObject->GetComponent<EngineZ::TransformComponent>();
    transform->SetWorldPosition(position);

    // Компоненты рендеринга
    auto renderer =
        gameObject->AddComponent<EngineZ::SpriteRendererComponent>();
    renderer->SetTexture(
        *EngineZ::ResourceSystem::Instance()->GetTextureMapElementShared(
            "enemies", 0));
    renderer->SetPixelSize(64, 64);

    // Физические компоненты
    auto rigidbody = gameObject->AddComponent<EngineZ::RigidbodyComponent>();
    rigidbody->SetKinematic(false);
    auto collider =
        gameObject->AddComponent<EngineZ::SpriteColliderComponent>();
    collider->SetTrigger(false);

    // Компоненты боя
    health = gameObject->AddComponent<HealthComponent>();
    armor = gameObject->AddComponent<ArmorComponent>();
    attack = gameObject->AddComponent<AttackComponent>();

    // ИИ компонент
    ai = gameObject->AddComponent<EnemyAIComponent>();

    // Настройка параметров
    health->SetHealth(50);
    armor->SetArmor(3);
    attack->SetDamage(10);
    attack->SetRange(70.0f);

    if (player) {
        ai->SetTarget(player->GetGameObject());
    }

    ai->SetMovementSpeed(120.0f);
    ai->SetAttackRange(70.0f);
    ai->SetVisionRange(250.0f);

    // Регистрируем здоровье в системе боя
    CombatSystem::Instance()->RegisterHealthComponent(health);
}

void Enemy::Update(float deltaTime) {

}

bool Enemy::IsAlive() const { return health && health->IsAlive(); }
}  // namespace Roguelike