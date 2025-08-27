#include <SFML/Graphics.hpp>

#include "../Engine/CameraComponent.h"
#include "../Engine/Engine.h"
#include "../Engine/GameWorld.h"
#include "../Engine/RenderSystem.h"
#include "../Engine/ResourceSystem.h"
#include "GameLevelManager.h"
#include "LevelManager.h"

using namespace EngineZ;
using namespace Roguelike;

int main() {
    // Инициализация
    LevelManager::Instance().Initialize();
    

    // Загрузка ресурсов
    ResourceSystem::Instance()->LoadTextureMap(
        "player", "Resources/TextureMaps/Player.png", {126, 96}, 17, false);
    ResourceSystem::Instance()->LoadTextureMap(
        "level_floors", "Resources/TextureMaps/Floor.png", {16, 16}, 49, false);
    ResourceSystem::Instance()->LoadTextureMap(
        "level_walls", "Resources/TextureMaps/Wall.png", {16, 16}, 48, false);
    ResourceSystem::Instance()->LoadTextureMap(
        "enemies", "Resources/TextureMaps/Enemy.png", {126, 96}, 17, false);
    ResourceSystem::Instance()->LoadSound("music",
                                          "Resources/Sounds/labyrinth.wav");
   
    GameLevelManager::Instance().Initialize();
    // Создание окна
    sf::RenderWindow* mainWindow =
        new sf::RenderWindow(sf::VideoMode(1280, 720), "Roguelike");
    RenderSystem::Instance()->SetMainWindow(mainWindow);

    // Создание камеры
    auto cameraObject = GameWorld::Instance()->CreateGameObject("MainCamera");
    auto camera = cameraObject->AddComponent<CameraComponent>();
    camera->SetWindow(mainWindow);
    camera->SetBaseResolution(1280, 720);

    // Настройка начальной позиции камеры
    auto currentLevel = GameLevelManager::Instance().GetCurrentLevel();
    if (currentLevel && currentLevel->player) {
        auto playerTransform = currentLevel->player->GetGameObject()
                                   ->GetComponent<TransformComponent>();
        if (playerTransform) {
            auto cameraTransform =
                cameraObject->GetComponent<TransformComponent>();
            cameraTransform->SetWorldPosition(
                playerTransform->GetWorldPosition());
            camera->SetFollowTarget(playerTransform);
        }
    }

    // Главный цикл
    sf::Clock gameClock;
    while (mainWindow->isOpen()) {
        sf::Event event;
        while (mainWindow->pollEvent(event)) {
            if (event.type == sf::Event::Closed) mainWindow->close();
        }

        float deltaTime = gameClock.restart().asSeconds();

        // Обновление уровня
        GameLevelManager::Instance().Update(deltaTime);

        // Обновление позиции камеры
        currentLevel = GameLevelManager::Instance().GetCurrentLevel();
        if (currentLevel && currentLevel->player) {
            auto playerTransform = currentLevel->player->GetGameObject()
                                       ->GetComponent<TransformComponent>();
            if (playerTransform) {
                auto cameraTransform =
                    cameraObject->GetComponent<TransformComponent>();
                auto playerPos = playerTransform->GetWorldPosition();
                auto currentPos = cameraTransform->GetWorldPosition();

                // Плавное следование камеры
                EngineZ::Vector2Df newPosition = {
                    currentPos.x +
                        (playerPos.x - currentPos.x) * 5.0f * deltaTime,
                    currentPos.y +
                        (playerPos.y - currentPos.y) * 5.0f * deltaTime};

                cameraTransform->SetWorldPosition(newPosition);
            }
        }

        // Отрисовка
        mainWindow->clear(sf::Color(30, 30, 30));
        Engine::Instance()->Run();
        mainWindow->display();
    }

    delete mainWindow;
    return 0;
}