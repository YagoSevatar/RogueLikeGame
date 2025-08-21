#include "DeveloperLevel.h"
#include <queue> 
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <set>
#include <cmath>
#include "CombatSystem.h"
#include "Enemy.h"
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
    // Очищаем данные
    walls.clear();
    floors.clear();
    enemies.clear();

    // Генерируем лабиринт
    MazeGenerator mazeGenerator(15, 15, this);
    mazeGenerator.Generate();
    const auto& mazeGrid = mazeGenerator.GetGrid();

    wallGrid = mazeGrid;

    // Создаем пол и стены на основе сгенерированного лабиринта
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 15; x++) {
            // создаем пол
            int floorType = 0;  // Базовый пол
            if (x == 0 || x == 14 || y == 0 || y == 14) {
                floorType = 1;  // Граничный пол
            }
            floors.push_back(std::make_unique<Floor>(
                EngineZ::Vector2Df{x * 128.f, y * 128.f}, floorType));

            // Создаем стену
            if (mazeGrid[y][x]) {
                int wallType = 12;  // Базовая стена

                // Определяем тип стены на основе соседей
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

    // Создаем игрока в центре
    centerX = 7 * 128.f + 64.f;
    centerY = 7 * 128.f + 64.f;
    player = std::make_shared<Player>(EngineZ::Vector2Df{centerX, centerY});

    // Создаем врагов в случайных свободных местах
    std::set<std::pair<int, int>> occupiedPositions;
    occupiedPositions.insert({7, 7});  // Позиция игрока

    for (int i = 0; i < 4; i++) {
        int x, y;
        int attempts = 0;
        do {
            x = 1 + rand() % 13;  
            y = 1 + rand() % 13;
            attempts++;

            if (attempts > 100) {
                std::cout << "Failed to find valid position for enemy after "
                             "100 attempts"
                          << std::endl;
                break;
            }
        } while (wallGrid[y][x] || occupiedPositions.count({x, y}));

        if (attempts <= 100) {
            occupiedPositions.insert({x, y});
            float posX = x * 128.f + 64.f;
            float posY = y * 128.f + 64.f;

            enemies.push_back(std::make_unique<Enemy>(
                EngineZ::Vector2Df{posX, posY}, player.get()));
            std::cout << "Enemy created at: (" << posX << ", " << posY << ")\n";
        }
    }

    // Создаем музыку
    music = std::make_unique<Music>("music");
}
void DeveloperLevel::EnsureConnectivity(std::vector<std::vector<int>>& grid) {
   
    std::vector<std::vector<int>> connectedGrid = grid;

    // Находим все изолированные области и соединяем их
    for (int y = 1; y < 14; y += 2) {
        for (int x = 1; x < 14; x += 2) {
            if (connectedGrid[y][x] == 1) continue;  // Пропускаем стены

            // Проверяем, является ли клетка изолированной
            if (IsIsolated(connectedGrid, x, y)) {
                // Соединяем с ближайшей не изолированной областью
                ConnectToMainArea(connectedGrid, x, y);
            }
        }
    }

    wallGrid = connectedGrid;
}
bool DeveloperLevel::IsIsolated(const std::vector<std::vector<int>>& grid,
                                int startX, int startY) {
    std::vector<std::vector<int>> visited(15, std::vector<int>(15, false));
    std::queue<std::pair<int, int>> queue;

    queue.push({startX, startY});
    visited[startY][startX] = true;
    int count = 0;

    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();
        count++;

        int x = current.first;
        int y = current.second;

        int dx[] = {0, 1, 0, -1};
        int dy[] = {-1, 0, 1, 0};

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < 15 && ny >= 0 && ny < 15 && !grid[ny][nx] &&
                !visited[ny][nx]) {
                visited[ny][nx] = true;
                queue.push({nx, ny});
            }
        }
    }

    // Если область слишком маленькая, считаем ее изолированной
    return count < 5;
}
void DeveloperLevel::ConnectToMainArea(std::vector<std::vector<int>>& grid,
                                       int startX, int startY) {
    // Ищем ближайшую не изолированную область
    int targetX = -1, targetY = -1;
    float minDistance = std::numeric_limits<float>::max();

    for (int y = 1; y < 14; y += 2) {
        for (int x = 1; x < 14; x += 2) {
            if (grid[y][x] || (x == startX && y == startY)) continue;

            if (!IsIsolated(grid, x, y)) {
                float distance = std::sqrt(std::pow(x - startX, 2) +
                                           std::pow(y - startY, 2));
                if (distance < minDistance) {
                    minDistance = distance;
                    targetX = x;
                    targetY = y;
                }
            }
        }
    }

    if (targetX != -1 && targetY != -1) {
        // Прокладываем путь между областями
        int x = startX, y = startY;

        while (x != targetX || y != targetY) {
            if (x < targetX) {
                x++;
            } else if (x > targetX) {
                x--;
            } else if (y < targetY) {
                y++;
            } else if (y > targetY) {
                y--;
            }

            grid[y][x] = false;  // Убираем стену
        }
    }
}
bool DeveloperLevel::IsEnemyAtPosition(int gridX, int gridY) const {
    float cellCenterX = gridX * 128.f + 64.f;
    float cellCenterY = gridY * 128.f + 64.f;

    for (const auto& enemy : enemies) {
        if (!enemy) continue;

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
bool DeveloperLevel::IsWallAtPosition(int gridX, int gridY) const {
    if (gridX < 0 || gridX >= 15 || gridY < 0 || gridY >= 15) {
        return true;
    }
    return wallGrid[gridY][gridX];
}

void DeveloperLevel::Update(float deltaTime) {
    // Обновляем систему боя
    CombatSystem::Instance()->Update();

    // Обновляем игрока
    if (player) {
        player->Update(deltaTime);
    }

    // Обновляем врагов
    for (auto& enemy : enemies) {
        enemy->Update(deltaTime);
    }

    // Удаляем мертвых врагов
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                                 [](const std::unique_ptr<Enemy>& enemy) {
                                     return !enemy->IsAlive();
                                 }),
                  enemies.end());
    if (player) {
        auto playerTransform =
            player->GetGameObject()
                ->GetComponent<EngineZ::TransformComponent>();
        if (playerTransform) {
            auto pos = playerTransform->GetWorldPosition();
            pos.x = std::max(64.0f, std::min(pos.x, 14 * 128.0f - 64.0f));
            pos.y = std::max(64.0f, std::min(pos.y, 14 * 128.0f - 64.0f));
            playerTransform->SetWorldPosition(pos);
        }
    }

    // Ограничиваем позицию врагов
    for (auto& enemy : enemies) {
        auto enemyTransform =
            enemy->GetGameObject()->GetComponent<EngineZ::TransformComponent>();
        if (enemyTransform) {
            auto pos = enemyTransform->GetWorldPosition();
            pos.x = std::max(64.0f, std::min(pos.x, 14 * 128.0f - 64.0f));
            pos.y = std::max(64.0f, std::min(pos.y, 14 * 128.0f - 64.0f));
            enemyTransform->SetWorldPosition(pos);
        }
    }
}
void DeveloperLevel::Restart() {
    Stop();
    Start();
}

void DeveloperLevel::Stop() { EngineZ::GameWorld::Instance()->Clear(); }
}  // namespace Roguelike