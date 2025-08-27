#include "GameLevelManager.h"

#include <iostream>

#include "LevelController.h"

namespace Roguelike {

GameLevelManager& GameLevelManager::Instance() {
    static GameLevelManager instance;
    return instance;
}

void GameLevelManager::Initialize() {
    // Инициализация контроллера уровней
    LevelController::Instance().Initialize();
    LoadNextLevel();
}

void GameLevelManager::Update(float deltaTime) {
    // Проверка запроса на смену уровня
    if (LevelManager::Instance().ShouldChangeLevel()) {
        LoadNextLevel();
        LevelManager::Instance().CompleteLevelChange();
        return;
    }

    // Обновление текущего активного уровня
    if (currentLevel) {
        currentLevel->Update(deltaTime);
    }
}

void GameLevelManager::LoadNextLevel() {
    // Очистка предыдущего уровня
    if (currentLevel) {
        currentLevel->Stop();
        currentLevel.reset();
    }

    // Создание нового уровня
    currentLevel = std::make_shared<Level1>();
    currentLevel->Start();
}

std::shared_ptr<BaseLevel> GameLevelManager::GetCurrentLevel() const {
    return currentLevel;
}

}  // namespace Roguelike