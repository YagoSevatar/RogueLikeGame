#include "Player.h"
#include "Enemy.h"
#include "Logger.h"
#include "HealthComponent.h"

namespace Roguelike
{
    Player::Player()
    {
        gameObject = EngineZ::GameWorld::Instance()->CreateGameObject("Player");

        auto playerRenderer = gameObject->AddComponent<EngineZ::SpriteRendererComponent>();
        auto playerInput = gameObject->AddComponent<EngineZ::InputComponent>();

        healthComponent = std::make_shared<EngineZ::HealthComponent>(gameObject, 100, 5);
        // Изменено: передаем raw pointer вместо shared_ptr
        gameObject->AddComponent(healthComponent.get());

        LOG_INFO("Player created with health component");
    }

    void Player::Attack(Enemy* enemy)
    {
        if (!enemy)
        {
            LOG_WARN("Attempt to attack null enemy");
            return;
        }

        auto enemyHealth = enemy->GetHealthComponent();
        if (enemyHealth->IsDead())
        {
            LOG_WARN("Attempt to attack already dead enemy");
            return;
        }

        LOG_INFO("Player attacks enemy for " + std::to_string(attackDamage) + " damage");
        enemyHealth->TakeDamage(attackDamage);
    }

    EngineZ::GameObject* Player::GetGameObject()
    {
        return gameObject;
    }
}