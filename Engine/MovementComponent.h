#pragma once
#include "Component.h"
#include "Vector.h"

namespace EngineZ {
class InputComponent;
class TransformComponent;
class SpriteAnimationComponent;

class MovementComponent : public Component {
   public:
    MovementComponent(GameObject* gameObject);
    ~MovementComponent();

    void Update(float deltaTime) override;
    void Render() override;

    void SetSpeed(float newSpeed);
    float GetSpeed() const;
    float GetAccelerationSquared() const;

   private:
    InputComponent* input;
    TransformComponent* transform;
    SpriteAnimationComponent* animationComponent;

    float speed = 0;
    Vector2Df previousPosition = {0, 0};
    Vector2Df acceleration = {0, 0};
};
}  // namespace EngineZ