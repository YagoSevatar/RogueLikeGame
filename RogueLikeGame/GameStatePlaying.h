#pragma once
#include "SFML/Graphics.hpp"
#include "GameStateData.h"
#include "ResourceSystem.h"

namespace Roguelike
{
    class GameStatePlayingData : public GameStateData
    {
    public:
        void Init() override;
        void HandleWindowEvent(const sf::Event& event) override;
        void Update(float timeDelta) override;
        void Draw(sf::RenderWindow& window) override;

    private:
        sf::Text m_mainText;
        sf::Text m_hintText;

        void centerText(sf::Text& text, float verticalOffset = 0.f);
    };
}