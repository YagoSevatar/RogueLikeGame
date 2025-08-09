#pragma once

#include <array>
#include <iostream>

#include "CombatSystem.h"
#include "Enemy.h"
#include "Floor.h"
#include "Music.h"
#include "Player.h"
#include "Scene.h"
#include "Wall.h"

using namespace EngineZ;

namespace Roguelike {
class DeveloperLevel : public Scene {
   public:
    void Start() override;
    void Restart() override;
    void Stop() override;

    std::vector<std::unique_ptr<Wall>> walls;
    std::vector<std::unique_ptr<Floor>> floors;

   private:
    std::shared_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::unique_ptr<Music> music;
};
}  // namespace Roguelike
