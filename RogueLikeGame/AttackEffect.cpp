#include "AttackEffect.h"

#include "../Engine/GameWorld.h"
#include "../Engine/ResourceSystem.h"
#include "../Engine/SpriteRendererComponent.h"
#include "../Engine/TransformComponent.h"

namespace Roguelike {
AttackEffect::AttackEffect(EngineZ::GameObject* owner, float duration)
    : totalDuration(duration) {
    // Создание игрового объекта для визуального эффекта атаки
    effectObject =
        EngineZ::GameWorld::Instance()->CreateGameObject("AttackEffect");
    auto transform = effectObject->GetComponent<EngineZ::TransformComponent>();
    auto renderer =
        effectObject->AddComponent<EngineZ::SpriteRendererComponent>();

    // Позиционирование эффекта относительно владельца
    auto ownerTransform = owner->GetComponent<EngineZ::TransformComponent>();
    if (ownerTransform) {
        transform->SetWorldPosition(ownerTransform->GetWorldPosition());
    }

    // Загрузка и настройка текстуры эффекта
    auto texture =
        EngineZ::ResourceSystem::Instance()->GetTextureShared("attack_effect");
    if (texture) {
        renderer->SetTexture(*texture);
        renderer->SetPixelSize(50, 50);
    }
}

void AttackEffect::Update(float deltaTime) {
    // Обновление таймера эффекта атаки
    currentTime += deltaTime;

    // Визуальные преобразования эффекта со временем
    if (auto transform =
            effectObject->GetComponent<EngineZ::TransformComponent>()) {
        float progress = currentTime / totalDuration;
        float scale = 1.0f + progress * 2.0f;  // Увеличение размера
        float alpha = 1.0f - progress;         // Уменьшение прозрачности

        transform->SetLocalScale({scale, scale});

        // Обновление цвета с учетом прозрачности
        if (auto renderer =
                effectObject
                    ->GetComponent<EngineZ::SpriteRendererComponent>()) {
            sf::Color color = sf::Color::Red;
            color.a = static_cast<sf::Uint8>(alpha * 255);
        }
    }
}

bool AttackEffect::IsFinished() const { return currentTime >= totalDuration; }

EngineZ::GameObject* AttackEffect::GetEffectObject() const {
    return effectObject;
}
}  // namespace Roguelike