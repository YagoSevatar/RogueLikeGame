#include "DeveloperLevel.h"

#include "Enemy.h"
#include "Floor.h"
#include "MazeGenerator.h"
#include "Music.h"
#include "Player.h"
#include "Wall.h"
#include "randomizer.h"

namespace {
// Вспомогательный класс для обновления боевой системы
class CombatUpdater : public EngineZ::Component {
   public:
    CombatUpdater(EngineZ::GameObject* gameObject) : Component(gameObject) {}

    void Update(float deltaTime) override {
        Roguelike::CombatSystem::Instance()->Update();
    }

    void Render() override {}
};
}  // namespace

namespace Roguelike {
void DeveloperLevel::Start() {
    int width = 15;
    int height = 15;

    // Генерация лабиринта
    for (int y = 0; y < height + 1; y++) {
        for (int x = 0; x < width + 1; x++) {
            // Если не стена - пол
            if (x != 0 && x != width && y != 0 && y != height) {
                floors.push_back(std::make_unique<Floor>(
                    EngineZ::Vector2Df{x * 128.f, y * 128.f}, 0));
            }

            // Углы
            if (x == 0 && y == 0)  // левый-нижний
            {
                walls.push_back(std::make_unique<Wall>(
                    EngineZ::Vector2Df{x * 128.f, y * 128.f}, 25));
            }
            if (x == width && y == 0)  // правый-нижний
            {
                walls.push_back(std::make_unique<Wall>(
                    EngineZ::Vector2Df{x * 128.f, y * 128.f}, 27));
            }
            if (x == 0 && y == height)  // левый-верхний
            {
                walls.push_back(std::make_unique<Wall>(
                    EngineZ::Vector2Df{x * 128.f, y * 128.f}, 1));
            }
            if (x == width && y == height)  // правый-верхний
            {
                walls.push_back(std::make_unique<Wall>(
                    EngineZ::Vector2Df{x * 128.f, y * 128.f}, 3));
            }

            // Границы
            if (x == 0 && y != height && y != 0)  // левая
            {
                floors.push_back(std::make_unique<Floor>(
                    EngineZ::Vector2Df{x * 128.f, y * 128.f}, 18));
                walls.push_back(std::make_unique<Wall>(
                    EngineZ::Vector2Df{x * 128.f, y * 128.f}, 12));
            }
            if (x == width && y != height && y != 0)  // правая
            {
                floors.push_back(std::make_unique<Floor>(
                    EngineZ::Vector2Df{x * 128.f, y * 128.f}, 19));
                walls.push_back(std::make_unique<Wall>(
                    EngineZ::Vector2Df{x * 128.f, y * 128.f}, 12));
            }
            if (y == 0 && x != width && x != 0)  // нижняя
            {
                walls.push_back(std::make_unique<Wall>(
                    EngineZ::Vector2Df{x * 128.f, y * 128.f}, 38));
            }
            if (y == height && x != width && x != 0)  // верхняя
            {
                walls.push_back(std::make_unique<Wall>(
                    EngineZ::Vector2Df{x * 128.f, y * 128.f}, 38));
            }
        }
    }

    // Генерация лабиринта
    MazeGenerator mazeGenerator(width, height, this);
    mazeGenerator.Generate();

    // Создать игрока
    player = std::make_shared<Player>(
        EngineZ::Vector2Df{width / 2 * 128.f, height / 2 * 128.f});

    // Создать врагов
    for (int i = 0; i < 5; i++) {
        float x = random(0.0f, static_cast<float>(width)) * 128.f;
        float y = random(0.0f, static_cast<float>(height)) * 128.f;
        enemies.push_back(std::make_unique<Enemy>(EngineZ::Vector2Df{x, y}));
    }

    // Создать музыку
    music = std::make_unique<Music>("music");

    // Создать объект для обновления боевой системы
    auto updaterObject =
        EngineZ::GameWorld::Instance()->CreateGameObject("CombatUpdater");
    updaterObject->AddComponent<CombatUpdater>();
}

void DeveloperLevel::Restart() {
    Stop();
    Start();
}

void DeveloperLevel::Stop() { EngineZ::GameWorld::Instance()->Clear(); }
}  // namespace Roguelike
