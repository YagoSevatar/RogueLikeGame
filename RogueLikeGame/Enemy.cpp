#include "Enemy.h"

#include "CombatSystem.h"
#include "GameWorld.h"
#include "HealthComponent.h"
#include "ResourceSystem.h"
#include "RigidbodyComponent.h"
#include "SpriteColliderComponent.h"
#include "SpriteRendererComponent.h"
#include "TransformComponent.h"

namespace Roguelike {
Enemy::Enemy(const EngineZ::Vector2Df& position)
    : gameObject(EngineZ::GameWorld::Instance()->CreateGameObject("Enemy")) {
    auto transform = gameObject->GetComponent<EngineZ::TransformComponent>();
    transform->SetWorldPosition(position);

    auto renderer =
        gameObject->AddComponent<EngineZ::SpriteRendererComponent>();
    renderer->SetTexture(
        *EngineZ::ResourceSystem::Instance()->GetTextureMapElementShared(
            "enemies", 0));
    renderer->SetPixelSize(100, 100);

    auto health = gameObject->AddComponent<HealthComponent>();
    health->SetHealth(50);
    CombatSystem::Instance()->RegisterHealthComponent(health);

    auto rigidbody = gameObject->AddComponent<EngineZ::RigidbodyComponent>();
    rigidbody->SetKinematic(false);

    auto collider =
        gameObject->AddComponent<EngineZ::SpriteColliderComponent>();
}

EngineZ::GameObject* Enemy::GetGameObject() const { return gameObject; }
}  // namespace Roguelike
