#pragma once
#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include <memory>
// Forward declaration
namespace Roguelike { class Player; }

namespace Roguelike
{
    class Enemy
    {
    public:
        Enemy();
        EngineZ::GameObject* GetGameObject();
        std::shared_ptr<EngineZ::HealthComponent> GetHealthComponent() { return healthComponent; }
        void Attack(Player* player);

    private:
        EngineZ::GameObject* gameObject;
        std::shared_ptr<EngineZ::HealthComponent> healthComponent;
        int attackDamage = 5;
    };
}