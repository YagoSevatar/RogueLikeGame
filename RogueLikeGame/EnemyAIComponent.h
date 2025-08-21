#pragma once
#include "../Engine/Component.h"

namespace Roguelike {
class EnemyAIComponent : public EngineZ::Component {
   public:
    EnemyAIComponent(EngineZ::GameObject* gameObject);
    void Update(float deltaTime) override;
    void Render() override {}

    void SetTarget(EngineZ::GameObject* target);
    void SetMovementSpeed(float speed);
    void SetAttackRange(float range);
    void SetVisionRange(float range);

   private:
    EngineZ::GameObject* target = nullptr;
    float movementSpeed = 150.0f;
    float attackRange = 100.0f;
    float visionRange = 300.0f;
};
}  // namespace Roguelike