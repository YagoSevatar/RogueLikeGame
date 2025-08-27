#include "HealthBarComponent.h"

#include "HealthComponent.h"

namespace Roguelike {
HealthBarComponent::HealthBarComponent(EngineZ::GameObject* gameObject)
    : EngineZ::Component(gameObject) {
}

void HealthBarComponent::Initialize() {
    if (isInitialized) return;

    healthComponent = gameObject->GetComponent<HealthComponent>();
    transformComponent =
        gameObject->GetComponent<EngineZ::TransformComponent>();
    isInitialized = true;
}

void HealthBarComponent::Update(float deltaTime) {
    if (!isInitialized) {
        Initialize();
    }
}

void HealthBarComponent::Render() {
    if (!isInitialized) {
        Initialize();
    }

    if (!healthComponent || !transformComponent) return;

    auto position = transformComponent->GetWorldPosition();
    sf::Vector2f barPosition =
        EngineZ::Convert<sf::Vector2f, EngineZ::Vector2Df>(position);
    barPosition.x -= width / 2.0f;
    barPosition.y += yOffset;

    int currentHealth = healthComponent->GetHealth();
    int maxHealth = healthComponent->GetMaxHealth();

    sf::RectangleShape background(sf::Vector2f(width, height));
    background.setPosition(barPosition);
    background.setFillColor(sf::Color::Black);
    EngineZ::RenderSystem::Instance()->Render(background);

    float healthPercentage = static_cast<float>(currentHealth) / maxHealth;
    sf::RectangleShape healthBar(
        sf::Vector2f(width * healthPercentage, height));
    healthBar.setPosition(barPosition);
    healthBar.setFillColor(sf::Color::Red);
    EngineZ::RenderSystem::Instance()->Render(healthBar);
}
}  // namespace Roguelike