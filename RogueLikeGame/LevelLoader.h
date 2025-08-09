#pragma once
#include <vector>
#include <string>
#include <memory>
#include <map>

namespace Roguelike {
	enum class BlockType
	{
		Simple,
		ThreeHit,
		Unbreackable
	};


	class LevelLoader final
	{
	public:
	
		~LevelLoader() = default;
		int GetLevelCount();
	private:

		static BlockType CharToBlockType(char symbol);
	};

}
