#pragma once

#include <SFML/Window.hpp>

#include "Component.h"

namespace EngineZ {
class InputComponent : public Component {
   public:
    InputComponent(GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    float GetHorizontalAxis() const;
    float GetVerticalAxis() const;

   private:
    float horizontalAxis = 0.f;
    float verticalAxis = 0.f;
};
}  // namespace EngineZ