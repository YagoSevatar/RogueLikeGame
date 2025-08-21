#include "AttackEffect.h"

#include "../Engine/GameWorld.h"
#include "../Engine/ResourceSystem.h"
#include "../Engine/SpriteRendererComponent.h"
#include "../Engine/TransformComponent.h"

namespace Roguelike {
AttackEffect::AttackEffect(EngineZ::GameObject* owner, float duration)
    : totalDuration(duration) {
    // Создаем объект для эффекта
    effectObject =
        EngineZ::GameWorld::Instance()->CreateGameObject("AttackEffect");
    auto transform = effectObject->GetComponent<EngineZ::TransformComponent>();
    auto renderer =
        effectObject->AddComponent<EngineZ::SpriteRendererComponent>();

    // Устанавливаем позицию
    auto ownerTransform = owner->GetComponent<EngineZ::TransformComponent>();
    if (ownerTransform) {
        transform->SetWorldPosition(ownerTransform->GetWorldPosition());
    }

    // Загружаем текстуру
    auto texture =
        EngineZ::ResourceSystem::Instance()->GetTextureShared("attack_effect");
    if (texture) {
        renderer->SetTexture(*texture);
        renderer->SetPixelSize(50, 50);
    }
}

void AttackEffect::Update(float deltaTime) {
    currentTime += deltaTime;

    // Анимация - увеличиваем размер
    if (auto transform =
            effectObject->GetComponent<EngineZ::TransformComponent>()) {
        float scale = 1.0f + (currentTime / totalDuration) * 2.0f;
        transform->SetLocalScale({scale, scale});
    }
}

bool AttackEffect::IsFinished() const { return currentTime >= totalDuration; }

EngineZ::GameObject* AttackEffect::GetEffectObject() const {
    return effectObject;
}
}  // namespace Roguelike