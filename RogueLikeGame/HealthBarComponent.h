#pragma once
#include <SFML/Graphics.hpp>

#include "../Engine/Component.h"
#include "../Engine/RenderSystem.h"
#include "../Engine/TransformComponent.h"

namespace Roguelike {
class HealthComponent;

class HealthBarComponent : public EngineZ::Component {
   public:
    HealthBarComponent(EngineZ::GameObject* gameObject);
    void Update(float deltaTime) override;
    void Render() override;

    void SetOffset(float yOffset) { this->yOffset = yOffset; }
    void SetSize(float width, float height) {
        this->width = width;
        this->height = height;
    }

    void Initialize();

   private:
    HealthComponent* healthComponent = nullptr;
    EngineZ::TransformComponent* transformComponent = nullptr;

    float width = 50.0f;
    float height = 5.0f;
    float yOffset = -40.0f;
    bool isInitialized = false; 
};
}  // namespace Roguelike