#pragma once

#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "GameObject.h"

namespace Roguelike
{
	class Player
	{
	public:
		Player();
		EngineZ::GameObject* GetGameObject();
	private:
		EngineZ::GameObject* gameObject;
	};
}