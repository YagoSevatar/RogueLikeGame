#include "ArmorBarComponent.h"

#include "ArmorComponent.h"

namespace Roguelike {
ArmorBarComponent::ArmorBarComponent(EngineZ::GameObject* gameObject)
    : EngineZ::Component(gameObject) {
   
}
void ArmorBarComponent::Initialize() {
    if (isInitialized) return;

    armorComponent = gameObject->GetComponent<ArmorComponent>();
    transformComponent =
        gameObject->GetComponent<EngineZ::TransformComponent>();
    isInitialized = true;
}
void ArmorBarComponent::Update(float deltaTime) {
    if (!isInitialized) {
        Initialize();
    }
}

void ArmorBarComponent::Render() {
    if (!isInitialized) {
        Initialize();
    }

    if (!armorComponent || !transformComponent) return;

    auto position = transformComponent->GetWorldPosition();
    sf::Vector2f barPosition =
        EngineZ::Convert<sf::Vector2f, EngineZ::Vector2Df>(position);
    barPosition.x -= width / 2.0f;
    barPosition.y += yOffset;

    int currentArmor = armorComponent->GetArmor();
    int maxArmor = armorComponent->GetMaxArmor();

    sf::RectangleShape background(sf::Vector2f(width, height));
    background.setPosition(barPosition);
    background.setFillColor(sf::Color::Black);
    EngineZ::RenderSystem::Instance()->Render(background);

    float armorPercentage = static_cast<float>(currentArmor) / maxArmor;
    sf::RectangleShape armorBar(
        sf::Vector2f(width * armorPercentage, height));
    armorBar.setPosition(barPosition);
    armorBar.setFillColor(sf::Color::Blue);
    EngineZ::RenderSystem::Instance()->Render(armorBar);
}
}  // namespace Roguelike