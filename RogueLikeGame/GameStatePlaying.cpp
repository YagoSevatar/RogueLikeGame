#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include <cassert>
#include "Logger.h"
namespace Roguelike
{
    void GameStatePlayingData::Init()
    {
        try {
            auto font = EngineZ::ResourceSystem::Instance()->GetFontShared("Roboto-Regular");
            if (!font) {
                LOG_ERROR("Failed to load font 'Roboto-Regular'");
                throw std::runtime_error("Font loading failed");
            }

            LOG_INFO("Initializing GameStatePlayingData");

            // Configure main text
            m_mainText.setFont(*font);
            m_mainText.setString("TO BE DONE...");
            m_mainText.setCharacterSize(48);
            m_mainText.setFillColor(sf::Color::White);
            centerText(m_mainText, -30.f);

            // Configure hint text
            m_hintText.setFont(*font);
            m_hintText.setString("Press Esc to exit to menu");
            m_hintText.setCharacterSize(24);
            m_hintText.setFillColor(sf::Color::White);
            centerText(m_hintText, 30.f);

            LOG_INFO("GameStatePlayingData initialized successfully");
        }
        catch (const std::exception& e) {
            LOG_ERROR("Exception in GameStatePlayingData::Init: " + std::string(e.what()));
            throw;
        }
    }

    void GameStatePlayingData::centerText(sf::Text& text, float verticalOffset)
    {
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f,
            textBounds.top + textBounds.height / 2.0f);
        text.setPosition(1280 / 2,
            720 / 2 + verticalOffset);
    }

    void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Escape)
        {
            Application::Instance().GetGame().ExitGame();
        }
    }

    void GameStatePlayingData::Update(float timeDelta)
    {

    }

    void GameStatePlayingData::Draw(sf::RenderWindow& window)
    {
        window.clear(sf::Color::Black);
        window.draw(m_mainText);
        window.draw(m_hintText);
    }
}