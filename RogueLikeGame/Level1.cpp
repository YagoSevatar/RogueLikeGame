#include "Level1.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "../Engine/GameWorld.h"
#include "../Engine/ResourceSystem.h"
#include "../Engine/SpriteColliderComponent.h"
#include "../Engine/SpriteRendererComponent.h"
#include "../Engine/TransformComponent.h"
#include "CombatSystem.h"
#include "LevelController.h"

namespace Roguelike {

Level1::Level1() : mazeGenerator(nullptr) { InitializeWallGrid(); }

Level1::~Level1() {
    if (mazeGenerator) {
        delete mazeGenerator;
    }
}

void Level1::InitializeWallGrid() {
    // Инициализация сетки стен размером 15x15
    wallGrid.resize(15, std::vector<int>(15, 0));

    // Создание границ уровня
    for (int i = 0; i < 15; i++) {
        wallGrid[0][i] = 1;   // Верхняя граница
        wallGrid[14][i] = 1;  // Нижняя граница
        wallGrid[i][0] = 1;   // Левая граница
        wallGrid[i][14] = 1;  // Правая граница
    }

    // Заполнение угловых клеток
    wallGrid[0][0] = 1;
    wallGrid[0][14] = 1;
    wallGrid[14][0] = 1;
    wallGrid[14][14] = 1;
}

void Level1::Start() {
    // Инициализация уровня при его запуске
    InitializeLevel();
}

void Level1::InitializeLevel() {
    // Очистка предыдущего состояния уровня
    walls.clear();
    floors.clear();
    enemies.clear();
    exitTrigger.reset();

    // Освобождение памяти генератора лабиринта
    if (mazeGenerator) {
        delete mazeGenerator;
        mazeGenerator = nullptr;
    }

    // Создание и генерация нового лабиринта
    mazeGenerator = new MazeGenerator(15, 15, nullptr);
    ApplyLevelTheme();

    mazeGenerator->Generate();
    const auto& mazeGrid = mazeGenerator->GetGrid();
    wallGrid = mazeGrid;

    // Гарантия что клетка выхода свободна
    wallGrid[13][13] = 0;

    // Создание визуального представления пола и стен
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 15; x++) {
            int floorType = 0;
            sf::Color floorColor = currentFloorColor;

            // Специальное оформление для выхода
            if (x == 13 && y == 13) {
                floorType = 2;
                floorColor = sf::Color::Yellow;
            }
            // Оформление граничных клеток
            else if (x == 0 || x == 14 || y == 0 || y == 14) {
                floorType = 1;
            }

            floors.push_back(std::make_unique<Floor>(
                EngineZ::Vector2Df{x * 128.f, y * 128.f}, floorType,
                floorColor));

            // Создание стен на основе сгенерированного лабиринта
            if (mazeGrid[y][x] == 1 && !(x == 13 && y == 13)) {
                int wallType = 1;
                walls.push_back(std::make_unique<Wall>(
                    EngineZ::Vector2Df{x * 128.f, y * 128.f}, wallType));
            }
        }
    }

    // Создание игрока в центре уровня
    centerX = 7 * 128.f + 64.f;
    centerY = 7 * 128.f + 64.f;
    player =
        std::make_shared<Player>(EngineZ::Vector2Df{centerX, centerY}, nullptr);

    // Создание триггера выхода
    float exitX = 13 * 128.f + 64.f;
    float exitY = 13 * 128.f + 64.f;
    exitTrigger =
        std::make_unique<ExitTrigger>(EngineZ::Vector2Df{exitX, exitY});

    // Подписка контроллера уровня на события выхода
    exitTrigger->AddObserver(&LevelController::Instance());

    // Создание врагов в случайных позициях
    std::set<std::pair<int, int>> occupiedPositions{{7, 7}};
    for (int i = 0; i < 4; i++) {
        int x, y, attempts = 0;
        do {
            x = 1 + rand() % 13;
            y = 1 + rand() % 13;
            attempts++;
        } while ((wallGrid[y][x] == 1 || occupiedPositions.count({x, y})) &&
                 attempts < 100);

        if (attempts < 100) {
            occupiedPositions.insert({x, y});
            float posX = x * 128.f + 64.f;
            float posY = y * 128.f + 64.f;
            enemies.push_back(std::make_unique<Enemy>(
                EngineZ::Vector2Df{posX, posY}, player.get()));
        }
    }

    // Создание фоновой музыки уровня
    music = std::make_unique<Music>("music");
}

void Level1::ApplyLevelTheme() {
    // Применение цветовой схемы текущего уровня
    auto& theme = LevelManager::Instance().GetCurrentTheme();
    currentFloorColor = theme.floorColor;
    currentWallColor = theme.wallColor;
}

void Level1::Update(float deltaTime) {
    CheckLevelCompletion();
    CombatSystem::Instance()->Update();

    // Удаляем мертвых врагов
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                                 [](const std::unique_ptr<Enemy>& enemy) {
                                     return !enemy->IsAlive();
                                 }),
                  enemies.end());

    if (player) {
        player->Update(deltaTime);
    }
}

void Level1::CheckLevelCompletion() {
    // Отслеживание позиции игрока относительно выхода для визуальной обратной
    // связи
    if (player && player->GetGameObject()) {
        auto transform = player->GetGameObject()
                             ->GetComponent<EngineZ::TransformComponent>();

        if (transform) {
            auto playerPos = transform->GetWorldPosition();
            float exitX = 13 * 128.f + 64.f;
            float exitY = 13 * 128.f + 64.f;

            float distance = std::sqrt(std::pow(playerPos.x - exitX, 2) +
                                       std::pow(playerPos.y - exitY, 2));
        }
    }
}

void Level1::Restart() {
    Stop();
    Start();
}

void Level1::Stop() {
    if (mazeGenerator) {
        delete mazeGenerator;
        mazeGenerator = nullptr;
    }
    EngineZ::GameWorld::Instance()->Clear();
}
}  // namespace Roguelike