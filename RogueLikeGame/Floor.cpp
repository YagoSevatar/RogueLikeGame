#include "Floor.h"

#include "../Engine/GameWorld.h"
#include "../Engine/ResourceSystem.h"
#include "../Engine/SpriteRendererComponent.h"

namespace Roguelike {
Floor::Floor(const EngineZ::Vector2Df& position, int textureMapIndex) {
    gameObject = EngineZ::GameWorld::Instance()->CreateGameObject("Floor");
    auto transform = gameObject->GetComponent<EngineZ::TransformComponent>();
    transform->SetWorldPosition(position);

    auto renderer =
        gameObject->AddComponent<EngineZ::SpriteRendererComponent>();
    auto texture =
        EngineZ::ResourceSystem::Instance()->GetTextureMapElementShared(
            "level_floors", textureMapIndex);
    if (texture) {
        renderer->SetTexture(*texture);
    }
    renderer->SetPixelSize(128, 128);
}
}  // namespace Roguelike