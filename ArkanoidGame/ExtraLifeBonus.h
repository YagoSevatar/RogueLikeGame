#pragma once
#include "Bonus.h"
#include "Game.h"

namespace RoguelikeGame
{
    class ExtraLifeBonus : public Bonus
    {
    public:
        ExtraLifeBonus(const sf::Vector2f& position);
        void Apply() override;
        void Remove() override {} 
    };
}