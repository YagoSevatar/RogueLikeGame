#pragma once

#include <SFML/Window.hpp>

#include "Component.h"

namespace EngineZ {
class InputComponent : public Component {
   public:
    InputComponent(GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;
    bool IsAttackPressed() const;
    float GetHorizontalAxis() const;
    float GetVerticalAxis() const;

   private:
    float horizontalAxis = 0.f;
    float verticalAxis = 0.f;
    bool attackPressed = false;
};
}  // namespace EngineZ