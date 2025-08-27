#include "pch.h"
#include "PhysicsSystem.h"
#include "SpriteRendererComponent.h"
namespace EngineZ
{
	PhysicsSystem* PhysicsSystem::Instance()
	{
		static PhysicsSystem physicsSystem;
		return &physicsSystem;
	}

	float PhysicsSystem::GetFixedDeltaTime() const
	{
		return fixedDeltaTime;
	}

	void PhysicsSystem::Update() {
            triggersEnteredPair.clear();

            for (int i = 0; i < colliders.size(); i++) {
                colliders[i]->bounds =
                    colliders[i]
                        ->GetGameObject()
                        ->GetComponent<SpriteRendererComponent>()
                        ->GetSprite()
                        ->getGlobalBounds();

                for (int j = i + 1; j < colliders.size(); j++) {
                    sf::FloatRect intersection;
                    if (colliders[i]->bounds.intersects(colliders[j]->bounds,
                                                        intersection)) {
                        if (colliders[i]->isTrigger ||
                            colliders[j]->isTrigger) {
                            if (triggersEnteredPair.find(colliders[i]) ==
                                    triggersEnteredPair.end() &&
                                triggersEnteredPair.find(colliders[j]) ==
                                    triggersEnteredPair.end()) {
                                auto trigger =
                                    new Trigger(colliders[i], colliders[j]);
                                colliders[i]->OnTriggerEnter(*trigger);
                                colliders[j]->OnTriggerEnter(*trigger);

                                triggersEnteredPair.emplace(colliders[i],
                                                            colliders[j]);
                            }
                        }
         
                        else {                  
                            auto body1 =
                                colliders[i]
                                    ->GetGameObject()
                                    ->GetComponent<RigidbodyComponent>();
                            auto body2 =
                                colliders[j]
                                    ->GetGameObject()
                                    ->GetComponent<RigidbodyComponent>();

                            sf::Vector2f resolution(0, 0);
                            if (intersection.width < intersection.height) {
                                resolution.x =
                                    intersection.width *
                                    (colliders[i]->bounds.left <
                                             colliders[j]->bounds.left
                                         ? -1
                                         : 1);
                            } else {
                                resolution.y = intersection.height *
                                               (colliders[i]->bounds.top <
                                                        colliders[j]->bounds.top
                                                    ? -1
                                                    : 1);
                            }

                            if (body1 && !body1->GetKinematic()) {
                                auto transform1 =
                                    colliders[i]
                                        ->GetGameObject()
                                        ->GetComponent<TransformComponent>();
                                transform1->MoveBy(
                                    Convert<Vector2Df, sf::Vector2f>(
                                        resolution * 0.5f));
                            }

                            if (body2 && !body2->GetKinematic()) {
                                auto transform2 =
                                    colliders[j]
                                        ->GetGameObject()
                                        ->GetComponent<TransformComponent>();
                                transform2->MoveBy(
                                    Convert<Vector2Df, sf::Vector2f>(
                                        resolution * -0.5f));
                            }

                            auto collision = Collision(
                                colliders[i], colliders[j], intersection);
                            colliders[i]->OnCollision(collision);
                            colliders[j]->OnCollision(collision);
                        }
                    }
                }
            }
        }
        
	void PhysicsSystem::Subscribe(ColliderComponent* collider)
	{
		std::cout << "Subscribe " << collider << std::endl;
		colliders.push_back(collider);
	}
	void PhysicsSystem::Unsubscribe(ColliderComponent* collider)
	{
		std::cout << "Unsubscribe " << collider << std::endl;

		colliders.erase(std::remove_if(colliders.begin(), colliders.end(), [collider](ColliderComponent* obj) { return obj == collider; }), colliders.end());
	}
}