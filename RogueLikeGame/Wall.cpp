#include "Wall.h"

#include "../Engine/GameWorld.h"
#include "../Engine/ResourceSystem.h"
#include "../Engine/RigidbodyComponent.h"
#include "../Engine/SpriteColliderComponent.h"
#include "../Engine/SpriteRendererComponent.h"

namespace Roguelike {
Wall::Wall(const EngineZ::Vector2Df position, int textureMapIndex) {
    gameObject = EngineZ::GameWorld::Instance()->CreateGameObject("Wall");
    auto transform = gameObject->GetComponent<EngineZ::TransformComponent>();
    transform->SetWorldPosition(position);

    auto renderer =
        gameObject->AddComponent<EngineZ::SpriteRendererComponent>();
    auto texture =
        EngineZ::ResourceSystem::Instance()->GetTextureMapElementShared(
            "level_walls", textureMapIndex);
    if (texture) {
        renderer->SetTexture(*texture);
    }
    renderer->SetPixelSize(128, 128);

    // Физические компоненты
    auto rigidbody = gameObject->AddComponent<EngineZ::RigidbodyComponent>();
    rigidbody->SetKinematic(true);
    auto collider =
        gameObject->AddComponent<EngineZ::SpriteColliderComponent>();
    collider->SetTrigger(false);
}
}  // namespace Roguelike