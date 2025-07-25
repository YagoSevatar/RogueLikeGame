#pragma once

#include <iostream>
#include <array>
#include "Scene.h"
#include "Player.h"

using namespace EngineZ;

namespace Roguelike
{
	class DeveloperLevel : public Scene
	{
	public:
		void Start() override;
		void Restart() override;
		void Stop() override;
	private:
		std::shared_ptr<Player> player;
	};
}