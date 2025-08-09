#include "Wall.h"

#include <SpriteColliderComponent.h>
#include <SpriteMovementAnimationComponent.h>

Roguelike::Wall::Wall(const EngineZ::Vector2Df position, int textureMapIndex) {
    gameObject = EngineZ::GameWorld::Instance()->CreateGameObject("Wall");
    auto transform = gameObject->GetComponent<EngineZ::TransformComponent>();
    transform->SetWorldPosition(position);

    auto renderer =
        gameObject->AddComponent<EngineZ::SpriteRendererComponent>();
    renderer->SetTexture(
        *EngineZ::ResourceSystem::Instance()->GetTextureMapElementShared(
            "level_walls", textureMapIndex));
    renderer->SetPixelSize(128, 128);

    auto rigidbody = gameObject->AddComponent<EngineZ::RigidbodyComponent>();
    rigidbody->SetKinematic(true);

    auto collider =
        gameObject->AddComponent<EngineZ::SpriteColliderComponent>();
}
