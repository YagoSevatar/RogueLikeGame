#pragma once
#include <iostream>

#include "../Engine/GameObject.h"
#include "../Engine/GameWorld.h"
#include "../Engine/ResourceSystem.h"
#include "../Engine/SpriteColliderComponent.h"
#include "../Engine/SpriteRendererComponent.h"
#include "../Engine/TransformComponent.h"
#include "LevelObserver.h"

namespace Roguelike {
class ExitTrigger : public LevelSubject {
   public:
    ExitTrigger(const EngineZ::Vector2Df& position);

    void OnTriggerEnter(EngineZ::Trigger trigger);
    EngineZ::GameObject* GetGameObject() const;

   private:
    EngineZ::GameObject* gameObject;
    EngineZ::SpriteRendererComponent* renderer;
    EngineZ::SpriteColliderComponent* collider;
    EngineZ::Vector2Df exitPosition;
};
}  // namespace Roguelike