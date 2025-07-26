#include "Enemy.h"
#include "Player.h"
#include "HealthComponent.h"
#include "Logger.h"

namespace Roguelike
{
    Enemy::Enemy()
    {
        gameObject = EngineZ::GameWorld::Instance()->CreateGameObject("Enemy");

        auto enemyRenderer = gameObject->AddComponent<EngineZ::SpriteRendererComponent>();

        healthComponent = std::make_shared<EngineZ::HealthComponent>(gameObject, 50, 2);
        // Изменено: передаем raw pointer вместо shared_ptr
        gameObject->AddComponent(healthComponent.get());

        LOG_INFO("Enemy created with health component");
    }

    void Enemy::Attack(Player* player)
    {
        if (!player)
        {
            LOG_WARN("Attempt to attack null player");
            return;
        }

        auto playerHealth = player->GetHealthComponent();
        if (playerHealth->IsDead())
        {
            LOG_WARN("Attempt to attack already dead player");
            return;
        }

        LOG_INFO("Enemy attacks player for " + std::to_string(attackDamage) + " damage");
        playerHealth->TakeDamage(attackDamage);
    }

    EngineZ::GameObject* Enemy::GetGameObject()
    {
        return gameObject;
    }
}