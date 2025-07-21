#include "Player.h"
#include <ResourceSystem.h>

namespace Roguelike
{
	Player::Player()
	{
		gameObject = EngineZ::GameWorld::Instance()->CreateGameObject();
		auto playerRenderer = gameObject->AddComponent<EngineZ::SpriteRendererComponent>();

		playerRenderer->SetTexture(*EngineZ::ResourceSystem::Instance()->GetTextureShared("ball"));
		playerRenderer->SetPixelSize(32, 32);

		auto playerCamera = gameObject->AddComponent<EngineZ::CameraComponent>();
		playerCamera->SetWindow(&EngineZ::RenderSystem::Instance()->GetMainWindow());
		playerCamera->SetBaseResolution(1280, 720);

		auto playerInput = gameObject->AddComponent<EngineZ::InputComponent>();
	}

	EngineZ::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}
}