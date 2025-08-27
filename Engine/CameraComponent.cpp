#include "pch.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "Vector.h"
#include "RenderSystem.h"
#include <iostream>


namespace EngineZ {
CameraComponent::CameraComponent(GameObject* gameObject)
    : Component(gameObject) {
    view = new sf::View(sf::FloatRect(0, 0, 800, 600));
    transform = gameObject->GetComponent<TransformComponent>();
    window = nullptr;
}

CameraComponent::~CameraComponent() { delete view; }

void CameraComponent::Update(float deltaTime) {
    if (!window) return;

    if (followTarget) {
        auto targetPosition = followTarget->GetWorldPosition();
        auto currentPosition = transform->GetWorldPosition();

        Vector2Df newPosition = {
            currentPosition.x + (targetPosition.x - currentPosition.x) *
                                    followSpeed * deltaTime,
            currentPosition.y + (targetPosition.y - currentPosition.y) *
                                    followSpeed * deltaTime};

        transform->SetWorldPosition(newPosition);
    }

    auto position = transform->GetWorldPosition();
    auto rotation = transform->GetWorldRotation();

    view->setCenter(Convert<sf::Vector2f, Vector2Df>(position));
    view->setRotation(rotation);

    window->setView(*view);
}

void CameraComponent::SetFollowTarget(TransformComponent* target) {
    followTarget = target;
    if (target) {
        transform->SetWorldPosition(target->GetWorldPosition());
    }
}

void CameraComponent::SetFollowSpeed(float speed) { followSpeed = speed; }

void CameraComponent::Render() {
    if (window == nullptr) {
        std::cout << "NULL window render." << std::endl;
    }
}

void CameraComponent::SetWindow(sf::RenderWindow* newWindow) {
    window = newWindow;
}

void CameraComponent::SetBaseResolution(int width, int height) {
    view->reset(sf::FloatRect(0, 0, width, height));
}

void CameraComponent::ZoomBy(float newZoom) {
    if (newZoom <= 0) {
        std::cout << "Not allowed zoom lesser or equal than zero." << std::endl;
        return;
    }
    view->zoom(newZoom);
}
}  // namespace EngineZ