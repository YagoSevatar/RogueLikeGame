#pragma once
#include "Component.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"
#include "TransformComponent.h"

namespace EngineZ {
class  CameraComponent : public Component {
   public:
    explicit CameraComponent(GameObject* gameObject);
    ~CameraComponent();

    virtual void Update(float deltaTime) override;
    virtual void Render() override;

    void SetWindow(sf::RenderWindow* newWindow);
    void ZoomBy(float newZoom);
    void SetFollowTarget(TransformComponent* target);
    void SetFollowSpeed(float speed);
    void SetBaseResolution(int width, int height);

   private:
    TransformComponent* transform;
    sf::RenderWindow* window = nullptr;
    sf::View* view;
    float followSpeed = 5.0f;
    TransformComponent* followTarget = nullptr;
};
}  // namespace EngineZ
