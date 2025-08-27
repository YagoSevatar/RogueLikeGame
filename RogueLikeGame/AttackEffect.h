#pragma once
#include "../Engine/GameObject.h"

namespace Roguelike {
class AttackEffect {
   public:
    AttackEffect(EngineZ::GameObject* owner, float duration);
    void Update(float deltaTime);
    bool IsFinished() const;
    EngineZ::GameObject* GetEffectObject() const;

   private:
    EngineZ::GameObject* effectObject;
    float totalDuration;
    float currentTime = 0.0f;
};
}  // namespace Roguelike