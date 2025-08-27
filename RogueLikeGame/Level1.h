#pragma once
#include "BaseLevel.h"
#include "MazeGenerator.h"

namespace Roguelike {
class Level1 : public BaseLevel {
   public:
    Level1();
    ~Level1();

    void Start() override;
    void Restart() override;
    void Stop() override;
    void Update(float deltaTime);

    void InitializeLevel();       
    void CheckLevelCompletion();  

   private:
    void InitializeWallGrid();
    void ApplyLevelTheme();

    std::vector<std::vector<int>> wallGrid;
    MazeGenerator* mazeGenerator;
    float centerX = 0.0f;
    float centerY = 0.0f;
    sf::Color currentFloorColor;
    sf::Color currentWallColor;
};
}  // namespace Roguelike