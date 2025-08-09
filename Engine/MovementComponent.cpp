#include "pch.h"
#include "MovementComponent.h"

EngineZ::MovementComponent::MovementComponent(GameObject* gameObject)
	: Component(gameObject)
{
	input = gameObject->GetComponent<InputComponent>();
	transform = gameObject->GetComponent<TransformComponent>();

	if (input == nullptr)
	{
		std::cout << "Need input component for movement" << std::endl;
		gameObject->RemoveComponent(this);
	}
}

void EngineZ::MovementComponent::Update(float deltaTime)
{
	float xAxis = input->GetHorizontalAxis();
	float yAxis = input->GetVerticalAxis();

	transform->MoveBy(speed * deltaTime * Vector2Df{ xAxis, yAxis });

	acceleration = transform->GetWorldPosition() - previousPosition;
	previousPosition = transform->GetWorldPosition();
}

void EngineZ::MovementComponent::Render()
{
}

void EngineZ::MovementComponent::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}

float EngineZ::MovementComponent::GetSpeed() const
{
	return speed;
}

float EngineZ::MovementComponent::GetAccelerationSquared() const
{
	return acceleration.x * acceleration.x + acceleration.y * acceleration.y;
}
