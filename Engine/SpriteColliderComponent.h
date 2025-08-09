#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "ColliderComponent.h"
#include "RenderSystem.h"
#include "SpriteRendererComponent.h"

namespace EngineZ {
class SpriteColliderComponent : public ColliderComponent {
   public:
    SpriteColliderComponent(GameObject* gameObject);
    ~SpriteColliderComponent();

    void Update(float deltaTime) override;
    void Render() override;

   private:
    const sf::Sprite* sprite;
};
}  // namespace EngineZ
