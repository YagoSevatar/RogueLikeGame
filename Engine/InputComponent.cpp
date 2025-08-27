#include "pch.h"
#include "InputComponent.h"

#include "Logger.h"


namespace EngineZ {
InputComponent::InputComponent(GameObject* gameObject)
    : Component(gameObject) {}

void InputComponent::Update(float deltaTime) {
    verticalAxis = 0.f;
    horizontalAxis = 0.f;
    attackPressed = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        verticalAxis += 1.0f;
        LOG_INFO("Move forward");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        verticalAxis -= 1.0f;
        LOG_INFO("Move backward");
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        horizontalAxis += 1.0f;
        LOG_INFO("Move right");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        horizontalAxis -= 1.0f;
        LOG_INFO("Move left");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
        sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        attackPressed = true;
        LOG_INFO("Attack pressed");
    }
}
void InputComponent::Render() {}

float InputComponent::GetHorizontalAxis() const { return horizontalAxis; }
float InputComponent::GetVerticalAxis() const { return verticalAxis; }
bool InputComponent::IsAttackPressed() const { return attackPressed; }
}  // namespace EngineZ
