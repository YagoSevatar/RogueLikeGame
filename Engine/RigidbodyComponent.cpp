#include "pch.h"
#include "RigidbodyComponent.h"

namespace EngineZ
{
	RigidbodyComponent::RigidbodyComponent(GameObject* gameObject) : Component(gameObject)
	{
		transform = gameObject->GetComponent<TransformComponent>();
	}

	void RigidbodyComponent::Update(float deltaTime) {
            // Ограничение максимальной скорости
            float maxSpeed = 300.0f;
            float currentSpeed = std::sqrt(linearVelocity.x * linearVelocity.x +
                                           linearVelocity.y * linearVelocity.y);

            if (currentSpeed > maxSpeed) {
                linearVelocity.x = linearVelocity.x * maxSpeed / currentSpeed;
                linearVelocity.y = linearVelocity.y * maxSpeed / currentSpeed;
            }

            transform->MoveBy(linearVelocity * deltaTime);
            transform->RotateBy(angleVelocity * deltaTime);

            linearVelocity =
                linearVelocity * (1.0f - linearDamping * deltaTime);
            angleVelocity = angleVelocity * (1.0f - angleDamping * deltaTime);

            if (std::abs(linearVelocity.x) < 0.1f) linearVelocity.x = 0;
            if (std::abs(linearVelocity.y) < 0.1f) linearVelocity.y = 0;
            if (std::abs(angleVelocity) < 0.1f) angleVelocity = 0;
        }
	void RigidbodyComponent::Render()
	{

	}

	void RigidbodyComponent::SetLinearVelocity(Vector2Df newLinearVelocity)
	{
		linearVelocity = newLinearVelocity;
	}
	void RigidbodyComponent::AddLinearVelocity(Vector2Df linearOffset)
	{
		linearVelocity = linearVelocity + linearOffset;
	}
	Vector2Df RigidbodyComponent::GetLinearVelocity() const
	{
		return linearVelocity;
	}

	void RigidbodyComponent::SetAngleVelocity(float newAngleVelocity)
	{
		angleVelocity = newAngleVelocity;
	}
	void RigidbodyComponent::AddAngleVelocity(float angleOffset)
	{
		angleVelocity += angleOffset;
	}
	float RigidbodyComponent::GetAngleVelocity() const
	{
		return angleVelocity;
	}

	void RigidbodyComponent::SetLinearDamping(float newLinearDamping)
	{
		linearDamping = newLinearDamping;
	}
	float RigidbodyComponent::GetLinearDamping() const
	{
		return linearDamping;
	}

	void RigidbodyComponent::SetAngleDamping(float newAngleDamping)
	{
		angleDamping = newAngleDamping;
	}
	float RigidbodyComponent::GetAngleDamping() const
	{
		return angleDamping;
	}

	void RigidbodyComponent::SetKinematic(bool newIsKinematic)
	{
		isKinematic = newIsKinematic;
	}
	bool RigidbodyComponent::GetKinematic() const
	{
		return isKinematic;
	}
}