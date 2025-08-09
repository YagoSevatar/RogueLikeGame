#include "Floor.h"

Roguelike::Floor::Floor(const EngineZ::Vector2Df& position,
                        int textureMapIndex) {
    gameObject = EngineZ::GameWorld::Instance()->CreateGameObject("Floor");
    auto transform = gameObject->GetComponent<EngineZ::TransformComponent>();
    transform->SetWorldPosition(position);

    auto renderer =
        gameObject->AddComponent<EngineZ::SpriteRendererComponent>();
    renderer->SetTexture(
        *EngineZ::ResourceSystem::Instance()->GetTextureMapElementShared(
            "level_floors", textureMapIndex));
    renderer->SetPixelSize(128, 128);
}
