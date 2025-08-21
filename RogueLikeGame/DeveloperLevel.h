#pragma once
#include <memory>
#include <vector>
#include <queue> 
#include <set> 
namespace Roguelike {
class Enemy;
class Player;
class Wall;
class Floor;
}  

#include "Music.h"
#include "Scene.h"

namespace Roguelike {
class DeveloperLevel : public Scene {
   public:
    DeveloperLevel();
    ~DeveloperLevel();

    void Start() override;
    void Restart() override;
    void Stop() override;
    bool IsIsolated(const std::vector<std::vector<int>>& grid, int startX,
                    int startY); 
    void EnsureConnectivity(std::vector<std::vector<int>>& grid);
    void ConnectToMainArea(std::vector<std::vector<int>>& grid, int startX,
                           int startY);  
    bool IsWallAtPosition(int gridX, int gridY) const;
    void InitializeWallGrid();
    void Update(float deltaTime);
    bool IsEnemyAtPosition(int gridX, int gridY) const;
    std::shared_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Wall>> walls;
    std::vector<std::unique_ptr<Floor>> floors;

   private:
    std::unique_ptr<Music> music;
    std::vector<std::vector<int>> wallGrid;

    float centerX = 0.0f;
    float centerY = 0.0f;
    std::vector<std::pair<int, int>> corners;
};
}  // namespace Roguelike