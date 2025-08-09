#pragma once
#include "Collidable.h"
#include "GameObject.h"
#include "IObserver.h"
#include "SFML/Graphics.hpp"

namespace Roguelike {
class Ball final : public GameObject, public Colladiable, public IObservable {
   public:
    Ball(const sf::Vector2f& position);
    ~Ball() = default;
    void Update(float timeDelta) override;

    void InvertDirectionX();
    void InvertDirectionY();

    bool GetCollision(std::shared_ptr<Colladiable> collidable) const override;
    void ChangeAngle(float x);
    void restart() override;
    void ChangeSpeed(float multipleSpeed);

   private:
    void OnHit();
    sf::Vector2f direction;
    float lastAngle = 90;
    float multiplySpeed = 1.f;
};
}  // namespace Roguelike
