#include <SFML/Graphics.hpp>
#include "CombatSystem.h"
#include "CameraComponent.h"
#include "DeveloperLevel.h"
#include "Engine.h"
#include "Matrix2D.h"
#include "Player.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"
using namespace Roguelike;
using namespace EngineZ;

int main() {
    sf::RenderWindow* mainWindow =
        new sf::RenderWindow(sf::VideoMode(1280, 720), "Roguelike");
    EngineZ::RenderSystem::Instance()->SetMainWindow(mainWindow);

    // Загрузка ресурсов
    EngineZ::ResourceSystem::Instance()->LoadTextureMap(
        "player", "Resources/TextureMaps/Player.png", {126, 96}, 17,
        false); 
    EngineZ::ResourceSystem::Instance()->LoadTextureMap(
        "level_floors", "Resources/TextureMaps/Floor.png", {16, 16}, 49, false);
    EngineZ::ResourceSystem::Instance()->LoadTextureMap(
        "level_walls", "Resources/TextureMaps/Wall.png", {16, 16}, 48, false);
    EngineZ::ResourceSystem::Instance()->LoadTextureMap(
        "enemies", "Resources/TextureMaps/Enemy.png", {126, 96}, 17, false);
    EngineZ::ResourceSystem::Instance()->LoadSound(
        "music", "Resources/Sounds/labyrinth.wav");
    EngineZ::ResourceSystem::Instance()->LoadTexture(
        "attack_effect", "Resources/Textures/attack_effect.png", true);

    auto developerLevel = std::make_shared<DeveloperLevel>();
    developerLevel->Start();
    // Создаем камеру отдельно от игрока
    auto cameraObject =
        EngineZ::GameWorld::Instance()->CreateGameObject("MainCamera");
    auto camera = cameraObject->AddComponent<EngineZ::CameraComponent>();
    camera->SetWindow(mainWindow);
    camera->SetBaseResolution(1280, 720);


    sf::Clock gameClock;
    while (mainWindow->isOpen()) {
        sf::Event event;
        while (mainWindow->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                mainWindow->close();
            }

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Space) {
                if (developerLevel->player) {
                    developerLevel->player->Attack();
                }
            }
        }
        if (developerLevel->player && camera) {
            auto playerTransform =
                developerLevel->player->GetGameObject()
                    ->GetComponent<EngineZ::TransformComponent>();
            if (playerTransform) {
                camera->SetFollowTarget(playerTransform);
                camera->SetFollowSpeed(5.0f);  
            }
        }
        float deltaTime = gameClock.restart().asSeconds();

        // Обновляем игру
        developerLevel->Update(deltaTime);

        // Обновляем позицию камеры 
        if (developerLevel->player) {
            auto playerTransform =
                developerLevel->player->GetGameObject()
                    ->GetComponent<EngineZ::TransformComponent>();
            auto cameraTransform =
                cameraObject->GetComponent<EngineZ::TransformComponent>();
            if (playerTransform && cameraTransform) {
                // Прямое следование за игроком 
                cameraTransform->SetWorldPosition(
                    playerTransform->GetWorldPosition());
            }
        }

        EngineZ::Engine::Instance()->Run();
    }

    delete mainWindow;
    return 0;
}