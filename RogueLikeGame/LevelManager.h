#pragma once
#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include <memory>
#include <vector>

namespace Roguelike {
struct LevelTheme {
    sf::Color floorColor;
    sf::Color wallColor;
    sf::Color playerColor;
    sf::Color enemyColor;
    sf::Color backgroundColor;
};

class LevelManager {
   public:
    static LevelManager& Instance() {
        static LevelManager instance;
        return instance;
    }

    void Initialize() {
        themes = {
            // Level 1 - Classic
            {sf::Color(200, 200, 200), sf::Color(100, 100, 100),
             sf::Color(0, 255, 0), sf::Color(255, 0, 0), sf::Color(30, 30, 30)},

            // Level 2 - Blue
            {sf::Color(100, 100, 255), sf::Color(50, 50, 150),
             sf::Color(0, 255, 255), sf::Color(255, 100, 100),
             sf::Color(20, 20, 40)},

            // Level 3 - Green
            {sf::Color(100, 255, 100), sf::Color(50, 150, 50),
             sf::Color(255, 255, 0), sf::Color(255, 100, 255),
             sf::Color(20, 40, 20)},

            // Level 4 - Red
            {sf::Color(255, 100, 100), sf::Color(150, 50, 50),
             sf::Color(255, 255, 255), sf::Color(0, 0, 255),
             sf::Color(40, 20, 20)}};

        // Сброс состояние!
        currentLevel = 0;
        changeLevelRequested = false;

    }

    void NextLevel() {
        currentLevel = (currentLevel + 1) % themes.size();
    }

    bool ShouldChangeLevel() const {
        return changeLevelRequested;
    }

    void RequestLevelChange() {
        changeLevelRequested = true;
    }

    void CompleteLevelChange() {   
        changeLevelRequested = false;
    }

    int GetCurrentLevel() const {
        return currentLevel;
    }

    const LevelTheme& GetCurrentTheme() const { return themes[currentLevel]; }

   private:
    LevelManager() : currentLevel(0), changeLevelRequested(false) {
    }

    std::vector<LevelTheme> themes;
    int currentLevel;
    bool changeLevelRequested;
};
}  // namespace Roguelike