#include <SFML/Graphics.hpp>
#include <iostream> 

int main()
{
   
    sf::RenderWindow window(sf::VideoMode(1280, 720), "RogueLike Game");
    
   
    sf::Font font;
    font.loadFromFile("Resources/Fonts/Roboto-Regular.ttf");
   

    sf::Text toBeDoneText;
    toBeDoneText.setFont(font);
    toBeDoneText.setString("TO BE DONE...");
    toBeDoneText.setCharacterSize(48);
    toBeDoneText.setFillColor(sf::Color::White);
    sf::FloatRect bounds = toBeDoneText.getLocalBounds();
    toBeDoneText.setOrigin(bounds.width/2, bounds.height/2);
    toBeDoneText.setPosition(640, 360 - 30); 

    sf::Text hintText("Press Esc to exit", font, 24);
    hintText.setFillColor(sf::Color::White);
    hintText.setOrigin(hintText.getLocalBounds().width/2, hintText.getLocalBounds().height/2);
    hintText.setPosition(640, 360 + 30);

    std::cout << "Entering main loop..." << std::endl;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || 
               (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(toBeDoneText);
        window.draw(hintText);
        window.display();
    }

    return 0;
}