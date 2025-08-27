#pragma once
#include <SFML/Graphics.hpp>

#include "../Engine/Component.h"
#include "../Engine/RenderSystem.h"
#include "../Engine/TransformComponent.h"

namespace Roguelike {
class ArmorComponent;

class ArmorBarComponent : public EngineZ::Component {
   public:
    ArmorBarComponent(EngineZ::GameObject* gameObject);
    void Update(float deltaTime) override;
    void Render() override;

    void SetOffset(float yOffset) { this->yOffset = yOffset; }
    void SetSize(float width, float height) {
        this->width = width;
        this->height = height;
    }
    void Initialize();
   private:
    ArmorComponent* armorComponent = nullptr;
    EngineZ::TransformComponent* transformComponent = nullptr;
    bool isInitialized = false;
    float width = 50.0f;
    float height = 5.0f;
    float yOffset = -30.0f;  
};
}  // namespace Roguelike