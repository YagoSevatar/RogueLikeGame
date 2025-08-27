#pragma once
#include <memory>
#include <vector>
#include "Music.h"
#include "../Engine/Scene.h"
#include "Enemy.h"
#include "ExitTrigger.h"
#include "Floor.h"
#include "Player.h"
#include "Wall.h"

namespace Roguelike {
class BaseLevel : public EngineZ::Scene {
   public:
    virtual ~BaseLevel() = default;

    virtual void Start() override = 0;
    virtual void Restart() override = 0;
    virtual void Stop() override = 0;
    virtual void Update(float deltaTime) = 0;

    std::shared_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Wall>> walls;
    std::vector<std::unique_ptr<Floor>> floors;
    std::unique_ptr<ExitTrigger> exitTrigger;
    std::unique_ptr<Music> music;
};
}  // namespace Roguelike