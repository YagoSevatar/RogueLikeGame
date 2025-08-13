#pragma once
#include <string>

namespace Roguelike {
class GameWorld {
   private:
    GameWorld() = default;

   public:
    static GameWorld& Instance() {
        static GameWorld gameWorld;
        return gameWorld;
    }

    // Resources path
    const std::string RESOURCES_PATH = "Resources/";
    const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
    const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
    const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";
    const std::string LEVELS_CONFIG_PATH = RESOURCES_PATH + "levels.config";

};
}  // namespace Roguelike

#define SETTINGS GameWorld::Instance()