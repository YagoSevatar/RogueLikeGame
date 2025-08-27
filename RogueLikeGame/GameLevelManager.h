#pragma once
#include <memory>

#include "BaseLevel.h"
#include "Level1.h"
#include "LevelManager.h"

namespace Roguelike {
class GameLevelManager {
   public:
    static GameLevelManager& Instance();

    void Initialize();
    void Update(float deltaTime);
    void LoadNextLevel();
    std::shared_ptr<BaseLevel> GetCurrentLevel() const;

   private:
    GameLevelManager() = default;
    std::shared_ptr<BaseLevel> currentLevel;
};
}  // namespace Roguelike