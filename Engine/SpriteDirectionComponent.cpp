#include "SpriteDirectionComponent.h"

#include "pch.h"

EngineZ::SpriteDirectionComponent::SpriteDirectionComponent(
    GameObject* gameObject)
    : Component(gameObject) {
    input = gameObject->GetComponent<InputComponent>();
    spriteRenderer = gameObject->GetComponent<SpriteRendererComponent>();
}

void EngineZ::SpriteDirectionComponent::Update(float deltaTime) {
    if (input->GetHorizontalAxis() < 0) {
        spriteRenderer->FlipX(true);
    }
    if (input->GetHorizontalAxis() > 0) {
        spriteRenderer->FlipX(false);
    }
}

void EngineZ::SpriteDirectionComponent::Render() {}
