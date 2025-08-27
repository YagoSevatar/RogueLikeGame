#include "DeveloperLevel.h"

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
#include "Enemy.h"
#include "ExitTrigger.h"
#include "Floor.h"
#include "MazeGenerator.h"
#include "Player.h"
#include "Wall.h"

namespace Roguelike {

DeveloperLevel::DeveloperLevel() { InitializeWallGrid(); }

DeveloperLevel::~DeveloperLevel() = default;

void DeveloperLevel::InitializeWallGrid() {
    wallGrid.resize(15, std::vector<int>(15, 0));

    for (int i = 0; i < 15; i++) {
        wallGrid[0][i] = true;
        wallGrid[14][i] = true;
        wallGrid[i][0] = true;
        wallGrid[i][14] = true;
    }

    wallGrid[0][0] = true;
    wallGrid[0][14] = true;
    wallGrid[14][0] = true;
    wallGrid[14][14] = true;
}

void DeveloperLevel::Start() {
    // Очистка предыдущего состояния уровня
    walls.clear();
    floors.clear();
    enemies.clear();
    attackEffects.clear();
    exitTrigger.reset();

    ApplyLevelTheme();

    // Генерация лабиринта
    MazeGenerator mazeGenerator(15, 15, this);
    mazeGenerator.Generate();
    const auto& mazeGrid = mazeGenerator.GetGrid();

    wallGrid = mazeGrid;

    // Создание пола и стен на основе лабиринта
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 15; x++) {
            int floorType = 0;  
            sf::Color floorColor = currentFloorColor;
            // Специальная клетка для выхода
            if (x == 13 && y == 13) {
                floorType = 2;  
                floorColor = sf::Color::Yellow;
            } else if (x == 0 || x == 14 || y == 0 || y == 14) {
                floorType = 1;  
            }

            floors.push_back(std::make_unique<Floor>(
                EngineZ::Vector2Df{x * 128.f, y * 128.f}, floorType,
                floorColor));

            // Создание стен
            if (mazeGrid[y][x]) {
                int wallType = 12;  

                bool top = y > 0 && mazeGrid[y - 1][x];
                bool right = x < 14 && mazeGrid[y][x + 1];
                bool bottom = y < 14 && mazeGrid[y + 1][x];
                bool left = x > 0 && mazeGrid[y][x - 1];

                if (top && right && bottom && left)
                    wallType = 16;  // Перекресток
                else if (top && right && bottom)
                    wallType = 11;  // T-образное соединение
                else if (top && right && left)
                    wallType = 14;
                else if (top && bottom && left)
                    wallType = 13;
                else if (right && bottom && left)
                    wallType = 12;
                else if (top && right)
                    wallType = 6;  // Угол
                else if (top && left)
                    wallType = 7;
                else if (bottom && right)
                    wallType = 8;
                else if (bottom && left)
                    wallType = 9;
                else if (top || bottom)
                    wallType = 2;  // Вертикальная стена
                else if (left || right)
                    wallType = 3;  // Горизонтальная стена
                else
                    wallType = 1;  // Одиночная стена

                walls.push_back(std::make_unique<Wall>(
                    EngineZ::Vector2Df{x * 128.f, y * 128.f}, wallType));
            }
        }
    }

    // Создание игрока в центре
    centerX = 7 * 128.f + 64.f;
    centerY = 7 * 128.f + 64.f;
    player =
        std::make_shared<Player>(EngineZ::Vector2Df{centerX, centerY}, this);

    // Создание выхода
    float exitX = 13 * 128.f + 64.f;
    float exitY = 13 * 128.f + 64.f;
    exitTrigger =std::make_unique<ExitTrigger>(EngineZ::Vector2Df{exitX, exitY});
    // Создание врагов в случайных позициях
    std::set<std::pair<int, int>> occupiedPositions;
    occupiedPositions.insert({7, 7});

    for (int i = 0; i < 4; i++) {
        int x, y;
        int attempts = 0;
        do {
            x = 1 + rand() % 13;
            y = 1 + rand() % 13;
            attempts++;
        } while (wallGrid[y][x] ||
                 occupiedPositions.count({x, y}) && attempts < 100);

        if (attempts < 100) {
            occupiedPositions.insert({x, y});
            float posX = x * 128.f + 64.f;
            float posY = y * 128.f + 64.f;
            enemies.push_back(std::make_unique<Enemy>(
                EngineZ::Vector2Df{posX, posY}, player.get()));
        }
    }

    music.reset(new Music("music"));
}

void DeveloperLevel::ApplyLevelTheme() {
    auto& theme = LevelManager::Instance().GetCurrentTheme();
    currentFloorColor = theme.floorColor;
    currentWallColor = theme.wallColor;
}

void DeveloperLevel::OnExitTriggerEnter(EngineZ::Trigger trigger) {
    // Проверка что вошедший объект - игрок
    if (player && player->GetGameObject() &&
        !LevelManager::Instance().ShouldChangeLevel()) {
        auto playerTransform =
            player->GetGameObject()
                ->GetComponent<EngineZ::TransformComponent>();

        if (playerTransform) {
            auto playerPos = playerTransform->GetWorldPosition();
            float exitX = 13 * 128.f + 64.f;
            float exitY = 13 * 128.f + 64.f;

            // Проверка расстояния до выхода
            float distance = std::sqrt(std::pow(playerPos.x - exitX, 2) +
                                       std::pow(playerPos.y - exitY, 2));

            // Завершение уровня при приближении к выходу
            if (distance < 100.f) {
                LevelManager::Instance().RequestLevelChange();
            }
        }
    }
}

void DeveloperLevel::CheckLevelCompletion() {
    // Отслеживание позиции игрока относительно выхода
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

void DeveloperLevel::Update(float deltaTime) {
    CheckLevelCompletion();

    // Обработка запроса на смену уровня
    if (LevelManager::Instance().ShouldChangeLevel()) {
        LevelManager::Instance().NextLevel();
        LevelManager::Instance().CompleteLevelChange();
        Restart();
        return;
    }

    // Обновление системы боя
    CombatSystem::Instance()->Update();

    // Обновление визуальных эффектов атаки
    for (auto it = attackEffects.begin(); it != attackEffects.end();) {
        (*it)->Update(deltaTime);
        if ((*it)->IsFinished()) {
            EngineZ::GameWorld::Instance()->DestroyGameObject(
                (*it)->GetEffectObject());
            it = attackEffects.erase(it);
        } else {
            ++it;
        }
    }

    // Удаление побежденных врагов
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                                 [](const std::unique_ptr<Enemy>& enemy) {
                                     return !enemy->IsAlive();
                                 }),
                  enemies.end());

    // Обновление состояния игрока
    if (player) {
        player->Update(deltaTime);
    }
}

void DeveloperLevel::Restart() {
    Stop();
    Start();
}

void DeveloperLevel::AddAttackEffect(AttackEffect* effect) {
    attackEffects.push_back(std::unique_ptr<AttackEffect>(effect));
}

void DeveloperLevel::Stop() { EngineZ::GameWorld::Instance()->Clear(); }

bool DeveloperLevel::IsWallAtPosition(int gridX, int gridY) const {
    if (gridX < 0 || gridX >= 15 || gridY < 0 || gridY >= 15) {
        return true;
    }
    return wallGrid[gridY][gridX];
}

bool DeveloperLevel::IsEnemyAtPosition(int gridX, int gridY) const {
    float cellCenterX = gridX * 128.f + 64.f;
    float cellCenterY = gridY * 128.f + 64.f;

    for (auto& enemy : enemies) {
        if (!enemy->IsAlive()) continue;

        auto enemyTransform =
            enemy->GetGameObject()->GetComponent<EngineZ::TransformComponent>();
        if (!enemyTransform) continue;

        auto enemyPos = enemyTransform->GetWorldPosition();
        float distance = std::sqrt(std::pow(enemyPos.x - cellCenterX, 2) +
                                   std::pow(enemyPos.y - cellCenterY, 2));

        if (distance < 64.f) {
            return true;
        }
    }

    return false;
}

void DeveloperLevel::EnsureConnectivity(std::vector<std::vector<int>>& grid) {
    // Реализация обеспечения связности
}

bool DeveloperLevel::IsIsolated(const std::vector<std::vector<int>>& grid,
                                int startX, int startY) const {
    return false;
}

void DeveloperLevel::ConnectToMainArea(std::vector<std::vector<int>>& grid,
                                       int startX, int startY) {
    // Реализация соединения областей
}
}  // namespace Roguelike