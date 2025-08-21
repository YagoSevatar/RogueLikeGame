#include "pch.h"
#include "MovementComponent.h"
#include "InputComponent.h"
#include "TransformComponent.h"
#include "SpriteAnimationComponent.h"
#include "Vector.h"
#include <iostream>
namespace EngineZ {
MovementComponent::MovementComponent(GameObject* gameObject)
    : Component(gameObject) {
    input = gameObject->GetComponent<InputComponent>();
    transform = gameObject->GetComponent<TransformComponent>();
    animationComponent = gameObject->GetComponent<SpriteAnimationComponent>();

    if (input == nullptr) {
        std::cout << "Need input component for movement" << std::endl;
        gameObject->RemoveComponent(this);
    }
}

MovementComponent::~MovementComponent() {}

void MovementComponent::Update(float deltaTime) {
    float xAxis = input->GetHorizontalAxis();
    float yAxis = input->GetVerticalAxis();

    transform->MoveBy(speed * deltaTime * Vector2Df{xAxis, -yAxis});

    acceleration = transform->GetWorldPosition() - previousPosition;
    previousPosition = transform->GetWorldPosition();

    // Управление анимацией
    if (animationComponent != nullptr) {
        if (xAxis != 0.0f || yAxis != 0.0f) {
            animationComponent->StartAnimation("Walk");
        } else {
            animationComponent->StartAnimation("Idle");
        }
    }
}

void MovementComponent::Render() {}

void MovementComponent::SetSpeed(float newSpeed) { speed = newSpeed; }

float MovementComponent::GetSpeed() const { return speed; }

float MovementComponent::GetAccelerationSquared() const {
    return acceleration.x * acceleration.x + acceleration.y * acceleration.y;
}
}  // namespace EngineZ