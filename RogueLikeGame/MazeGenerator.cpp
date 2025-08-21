#include "MazeGenerator.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>
#include <chrono>
#include <random>
#include "DeveloperLevel.h"
#include "Floor.h"
#include "Wall.h"
#include "../Engine/Vector.h"

namespace Roguelike {
MazeGenerator::MazeGenerator(int width, int height, DeveloperLevel* level)
    : width(width), height(height), level(level) {
    grid.resize(height, std::vector<int>(width, 1));  // 1 = стена, 0 = проход
    rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

void MazeGenerator::Generate() {
    // Заполняем все клетки стенами
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid[y][x] = 1;  // Стена
        }
    }

    int startX = 1;
    int startY = 1;

    std::stack<std::pair<int, int>> stack;
    stack.push({startX, startY});
    grid[startY][startX] = 0; 

    // Направления: вверх, вправо, вниз, влево
    int dx[] = {0, 2, 0, -2};
    int dy[] = {-2, 0, 2, 0};

    while (!stack.empty()) {
        auto current = stack.top();
        int x = current.first;
        int y = current.second;

        // Получаем все возможные направления
        std::vector<int> directions;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx > 0 && nx < width - 1 && ny > 0 && ny < height - 1 &&
                grid[ny][nx] == 1) {
                directions.push_back(i);
            }
        }

        if (!directions.empty()) {
            // Выбираем случайное направление
            std::uniform_int_distribution<int> dist(0, directions.size() - 1);
            int dir = directions[dist(rng)];

            int nx = x + dx[dir];
            int ny = y + dy[dir];

            // Убираем стену между текущей и следующей клеткой
            grid[y + dy[dir] / 2][x + dx[dir] / 2] = 0;
            grid[ny][nx] = 0;

            stack.push({nx, ny});
        } else {
            stack.pop();
        }
    }

    // Добавляем вход и выход
    grid[1][0] = 0;                   // Вход
    grid[height - 2][width - 1] = 0;  // Выход
}
void MazeGenerator::AddFrontierCells(
    int x, int y, std::vector<std::pair<int, int>>& frontier) {
    // Проверяем все четыре направления
    int dx[] = {0, 2, 0, -2};
    int dy[] = {2, 0, -2, 0};

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx > 0 && nx < width - 1 && ny > 0 && ny < height - 1 &&
            grid[ny][nx]) {
            grid[ny][nx] = false;  // Делаем проход
            frontier.push_back({nx, ny});
        }
    }
}
void MazeGenerator::ConnectToPassage(int x, int y) {
    // Список возможных направлений для соединения
    std::vector<std::pair<int, int>> directions;
    int dx[] = {0, 2, 0, -2};
    int dy[] = {2, 0, -2, 0};

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // Проверяем, является ли клетка проходом
        if (nx > 0 && nx < width - 1 && ny > 0 && ny < height - 1 &&
            !grid[ny][nx]) {
            directions.push_back({dx[i] / 2, dy[i] / 2});
        }
    }

    if (!directions.empty()) {
        // Выбираем случайное направление
        auto dir = directions[rand() % directions.size()];
        // Делаем проход между клетками
        grid[y + dir.second][x + dir.first] = false;
    }
}
std::vector<std::pair<int, int>> MazeGenerator::GetAvailableDirections(int x,
                                                                       int y) {
    std::vector<std::pair<int, int>> directions = {
        {0, -2}, {0, 2}, {-2, 0}, {2, 0}};

    std::vector<std::pair<int, int>> available;

    for (const auto& dir : directions) {
        int nx = x + dir.first;
        int ny = y + dir.second;

        if (nx >= 0 && nx < width && ny >= 0 && ny < height && !grid[ny][nx]) {
            available.push_back(dir);
        }
    }

    return available;
}

void MazeGenerator::RemoveWall(int x1, int y1, int x2, int y2) {
    int wallX = (x1 + x2) / 2;
    int wallY = (y1 + y2) / 2;

    // Создаем пол в клетках
    level->floors.push_back(
        std::make_unique<Floor>(EngineZ::Vector2Df{x1 * 128.f, y1 * 128.f}, 0));
    level->floors.push_back(
        std::make_unique<Floor>(EngineZ::Vector2Df{x2 * 128.f, y2 * 128.f}, 0));

    // Создаем стену между клетками, если это необходимо
    if (wallX != x1 || wallY != y1) {
        level->walls.push_back(std::make_unique<Wall>(
            EngineZ::Vector2Df{wallX * 128.f, wallY * 128.f}, 14));

      
    }
}
}  // namespace Roguelike