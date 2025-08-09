// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>

#include "DeveloperLevel.h"
#include "Engine.h"
#include "Matrix2D.h"
#include "Player.h"
#include "ResourceSystem.h"

using namespace Roguelike;

int main() {
    EngineZ::RenderSystem::Instance()->SetMainWindow(
        new sf::RenderWindow(sf::VideoMode(1280, 720), "Roguelike"));

    ResourceSystem::Instance()->LoadTextureMap(
        "player", "Resources/TextureMaps/Player.png", {48, 63}, 4, false);
    ResourceSystem::Instance()->LoadTextureMap(
        "level_floors", "Resources/TextureMaps/Floor.png", {16, 16}, 49, false);
    ResourceSystem::Instance()->LoadTextureMap(
        "level_walls", "Resources/TextureMaps/Wall.png", {16, 16}, 48, false);
    ResourceSystem::Instance()->LoadTextureMap(
        "enemies", "Resources/TextureMaps/Enemy.png", {48, 63}, 4, false);
    ResourceSystem::Instance()->LoadSound("music",
                                          "Resources/Sounds/labyrinth.wav");

    auto developerLevel = std::make_shared<DeveloperLevel>();
    developerLevel->Start();

    EngineZ::Engine::Instance()->Run();

    return 0;
}
