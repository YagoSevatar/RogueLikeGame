#pragma once
#include "Collidable.h"
#include "GameObject.h"
#include "SFML/Graphics.hpp"

namespace Roguelike {
class Platform : public GameObject, public Colladiable {
   public:
    Platform(const sf::Vector2f& position);
    void Update(float timeDelta) override;

    bool GetCollision(std::shared_ptr<Colladiable> collidable) const override;
    void OnHit() override {}
    bool CheckCollision(std::shared_ptr<Colladiable> collidable) override;
    void ChangeWidth(float multiplyWidth);

   private:
    void Move(float speed);
};
}  // namespace Roguelike