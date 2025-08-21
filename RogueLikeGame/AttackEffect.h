#pragma once
#include "../Engine/GameObject.h"

namespace Roguelike {
class AttackEffect {
   public:
    AttackEffect(EngineZ::GameObject* owner, float duration);
    void Update(float deltaTime);
    bool IsFinished() const;
    EngineZ::GameObject* GetEffectObject() const;  // Добавляем геттер

   private:
    EngineZ::GameObject* effectObject;  // Делаем приватным
    float totalDuration;
    float currentTime = 0.0f;
};
}  // namespace Roguelike