#include "Floor.h"

namespace Roguelike {
Floor::Floor(const EngineZ::Vector2Df& position, int textureMapIndex,
             const sf::Color& color) {
    gameObject = EngineZ::GameWorld::Instance()->CreateGameObject("Floor");
    auto transform = gameObject->GetComponent<EngineZ::TransformComponent>();
    transform->SetWorldPosition(position);

    // Создание визуального представления пола
    auto renderer =
        gameObject->AddComponent<EngineZ::SpriteRendererComponent>();
    auto texture =
        EngineZ::ResourceSystem::Instance()->GetTextureMapElementShared(
            "level_floors", textureMapIndex);

    if (texture) {
        renderer->SetTexture(*texture);
    }
    renderer->SetPixelSize(128, 128);

    // Специальное оформление для выхода (желтый цвет)
    if (textureMapIndex == 2) {
        sf::Sprite* sprite = const_cast<sf::Sprite*>(renderer->GetSprite());
        if (sprite) {
            sprite->setColor(sf::Color::Yellow);
        }
    } else {
        // Обычный пол с заданным цветом
        sf::Sprite* sprite = const_cast<sf::Sprite*>(renderer->GetSprite());
        if (sprite) {
            sprite->setColor(color);
        }
    }
}
}
  // namespace Roguelike