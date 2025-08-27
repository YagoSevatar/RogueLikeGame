#pragma once
#include <memory>
#include <vector>

#include "../Engine/Scene.h"
#include "AttackEffect.h"
#include "ExitTrigger.h"
#include "LevelManager.h"
#include "Music.h"

namespace Roguelike {
class Enemy;
class Player;
class Wall;
class Floor;

class DeveloperLevel : public EngineZ::Scene {
   public:
    DeveloperLevel();
    ~DeveloperLevel();

    void Start() override;
    void Restart() override;
    void Stop() override;
    void Update(float deltaTime) ;

    bool IsWallAtPosition(int gridX, int gridY) const;
    void InitializeWallGrid();
    void ApplyLevelTheme();

    std::shared_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Wall>> walls;
    std::vector<std::unique_ptr<Floor>> floors;
    void AddAttackEffect(AttackEffect* effect);
    void CheckLevelCompletion();
    void OnExitTriggerEnter(
        EngineZ::Trigger trigger);  

   private:
    std::unique_ptr<Music> music;
    std::vector<std::unique_ptr<AttackEffect>> attackEffects;
    std::vector<std::vector<int>> wallGrid;
    std::unique_ptr<ExitTrigger> exitTrigger;  

    void EnsureConnectivity(std::vector<std::vector<int>>& grid);
    bool IsIsolated(const std::vector<std::vector<int>>& grid, int startX,
                    int startY) const;
    void ConnectToMainArea(std::vector<std::vector<int>>& grid, int startX,
                           int startY);
    bool IsEnemyAtPosition(int gridX, int gridY) const;
    float centerX = 0.0f;
    float centerY = 0.0f;
    std::vector<std::pair<int, int>> corners;

    sf::Color currentFloorColor;
    sf::Color currentWallColor;
};
}  // namespace Roguelike