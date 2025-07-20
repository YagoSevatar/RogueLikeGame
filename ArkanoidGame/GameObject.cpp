#include "GameObject.h"
#include "Sprite.h"

namespace RoguelikeGame
{
	void GameObject::Draw(sf::RenderWindow& window)
	{
		DrawSprite(sprite, window);
	}
}