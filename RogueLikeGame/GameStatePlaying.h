#pragma once
#include <unordered_map>

#include "Ball.h"
#include "BlockFactory.h"
#include "Bonus.h"
#include "GameStateData.h"
#include "IObserver.h"
#include "LevelLoader.h"
#include "Platform.h"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

namespace Roguelike {
class Game;
class Block;
class BlockFactory;

enum class BonusType {
    BiggerPlatform,
    SlowBall,

    Count
};

class GameStatePlayingData
    : public GameStateData,
      public IObserver,
      public std::enable_shared_from_this<GameStatePlayingData> {
   public:
    void Init() override;
    void HandleWindowEvent(const sf::Event& event) override;
    void Update(float timeDelta) override;
    void Draw(sf::RenderWindow& window) override;
    void LoadNextLevel();
    void Notify(std::shared_ptr<IObservable> observable) override;

   private:
    void createBlocks();
    void GetBallInverse(const sf::Vector2f& ballPos,
                        const sf::FloatRect& blockRect, bool& needInverseDirX,
                        bool& needInverseDirY);

    // Resources
    sf::Texture appleTexture;
    sf::Texture rockTexture;
    sf::Font font;
    sf::SoundBuffer eatAppleSoundBuffer;
    sf::SoundBuffer gameOverSoundBuffer;
    sf::SoundBuffer bonusSoundBuffer;

    // Game data
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    std::vector<std::shared_ptr<Block>> blocks;

    // UI data
    sf::Text scoreText;
    sf::Text inputHintText;
    sf::RectangleShape background;

    // Sounds
    sf::Sound gameOverSound;
    sf::Sound bonusSound;

    // Blocks creator
    std::unordered_map<BlockType, std::unique_ptr<BlockFactory>> factories;
    int breackableBlocksCount = 0;

    // Levels
    LevelLoader levelLoder;
    int currentLevel = 0;

    // Bonus
    std::map<BonusType, Bonus> bonuses;
};
}  // namespace Roguelike
