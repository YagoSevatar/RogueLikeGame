#include "Player.h"

#include "CameraComponent.h"
#include "CombatSystem.h"
#include "HealthComponent.h"
#include "InputComponent.h"
#include "MovementComponent.h"
#include "ResourceSystem.h"
#include "RigidbodyComponent.h"
#include "SpriteColliderComponent.h"
#include "SpriteDirectionComponent.h"
#include "SpriteMovementAnimationComponent.h"
#include "SpriteRendererComponent.h"
#include "TransformComponent.h"

namespace Roguelike {
Player::Player(const EngineZ::Vector2Df& position)
    : gameObject(EngineZ::GameWorld::Instance()->CreateGameObject("Player")) {
    auto transform = gameObject->GetComponent<EngineZ::TransformComponent>();
    transform->SetWorldPosition(position);

    auto renderer =
        gameObject->AddComponent<EngineZ::SpriteRendererComponent>();
    renderer->SetTexture(
        *EngineZ::ResourceSystem::Instance()->GetTextureMapElementShared(
            "player", 0));
    renderer->SetPixelSize(100, 100);

    auto camera = gameObject->AddComponent<EngineZ::CameraComponent>();
    camera->SetWindow(&EngineZ::RenderSystem::Instance()->GetMainWindow());
    camera->SetBaseResolution(1280, 720);

    auto input = gameObject->AddComponent<EngineZ::InputComponent>();

    auto movement = gameObject->AddComponent<EngineZ::MovementComponent>();
    movement->SetSpeed(400.f);

    auto spriteDirection =
        gameObject->AddComponent<EngineZ::SpriteDirectionComponent>();

    auto rigidbody = gameObject->AddComponent<EngineZ::RigidbodyComponent>();
    rigidbody->SetKinematic(false);

    auto collider =
        gameObject->AddComponent<EngineZ::SpriteColliderComponent>();

    auto animator =
        gameObject->AddComponent<EngineZ::SpriteMovementAnimationComponent>();
    animator->Initialize("player", 6.f);

    auto health = gameObject->AddComponent<HealthComponent>();
    health->SetHealth(100);

    CombatSystem::Instance()->RegisterHealthComponent(health);
}

EngineZ::GameObject* Player::GetGameObject() { return gameObject; }
}  // namespace Roguelike
