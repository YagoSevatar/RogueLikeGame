#pragma once
#include <stack>
#include <vector>
#include <random> 
#include <chrono> 
#include "DeveloperLevel.h"

    namespace Roguelike {
    class MazeGenerator {
       public:
        MazeGenerator(int width, int height, DeveloperLevel* level);
        void Generate();
        const std::vector<std::vector<int>>& GetGrid() const { return grid; } 
        void ConnectToPassage(int x, int y);
        void AddFrontierCells(int x, int y,std::vector<std::pair<int, int>>& frontier);
       private:
        int width, height;
        DeveloperLevel* level;
        std::vector<std::vector<int>> grid;
        std::mt19937 rng;
        std::vector<std::pair<int, int>> GetAvailableDirections(int x, int y);
        void RemoveWall(int x1, int y1, int x2, int y2);
    };
}  // namespace Roguelike