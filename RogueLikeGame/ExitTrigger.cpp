#include "ExitTrigger.h"

#include <iostream>

namespace Roguelike {

ExitTrigger::ExitTrigger(const EngineZ::Vector2Df& position) {
    gameObject =
        EngineZ::GameWorld::Instance()->CreateGameObject("ExitTrigger");
    auto transform = gameObject->GetComponent<EngineZ::TransformComponent>();
    transform->SetWorldPosition(position);

    // Визуальное представление выхода
    renderer = gameObject->AddComponent<EngineZ::SpriteRendererComponent>();
    auto texture =
        EngineZ::ResourceSystem::Instance()->GetTextureMapElementShared(
            "level_floors", 2);
    if (texture) {
        renderer->SetTexture(*texture);
    }
    renderer->SetPixelSize(128, 128);

    // Коллайдер для обнаружения входа игрока
    collider = gameObject->AddComponent<EngineZ::SpriteColliderComponent>();
    collider->SetTrigger(true);

    // Подписка на событие входа в триггер
    collider->SubscribeTriggerEnter(
        [this](EngineZ::Trigger trigger) { this->OnTriggerEnter(trigger); });

    exitPosition = position;
}

void ExitTrigger::OnTriggerEnter(EngineZ::Trigger trigger) {
    // Уведомление о завершении уровня
    NotifyLevelCompleted();
}

EngineZ::GameObject* ExitTrigger::GetGameObject() const { return gameObject; }
}  // namespace Roguelike