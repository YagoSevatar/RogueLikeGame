#include "LevelLoader.h"

#include <assert.h>

#include <filesystem>
#include <fstream>

#include "GameSettings.h"

namespace Roguelike {
Level& LevelLoader::GetLevel(int i) { return levels.at(i); }



void LevelLoader::LoadLevelsFromFile() {
    std::string filepath = SETTINGS.LEVELS_CONFIG_PATH;
    std::string line;
    std::ifstream file(filepath);
    int y = 0;

    file.close();
}

int LevelLoader::GetLevelCount() { return levels.size(); }
}  // namespace Roguelike