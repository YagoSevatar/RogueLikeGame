#pragma once

#include "CameraComponent.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "InputComponent.h"
#include "RenderSystem.h"
#include "SpriteRendererComponent.h"
#include "Vector.h"

namespace Roguelike {
class Player {
   public:
    Player(const EngineZ::Vector2Df& position);
    EngineZ::GameObject* GetGameObject();

   private:
    EngineZ::GameObject* gameObject;
};
}  // namespace Roguelike
