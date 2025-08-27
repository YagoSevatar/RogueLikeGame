#pragma once
#include <iostream>

#include "GameLevelManager.h"
#include "LevelManager.h"
#include "LevelObserver.h"

namespace Roguelike {
class LevelController : public LevelObserver {
   public:
    static LevelController& Instance() {
        static LevelController instance;
        return instance;
    }

    void Initialize() {
    }

    void OnLevelCompleted() override {
        if (!LevelManager::Instance().ShouldChangeLevel()) {
            LevelManager::Instance().RequestLevelChange();
        }
    }

    void OnLevelFailed() override {
        GameLevelManager::Instance().LoadNextLevel();
    }

   private:
    LevelController() = default;
};
}  // namespace Roguelike