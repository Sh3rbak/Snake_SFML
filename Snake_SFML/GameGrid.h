#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include "GameSettings.h"
#include "Math.h"

namespace SnakeGame
{
	enum class GameItemType
	{
		None,
		Apple,
		Snake
	};

	struct Apple;
	struct Snake;
	struct GridCell
	{
		Position position;
		GameItemType type = GameItemType::None;
	};

	void ChangeTypeCell(GridCell& gridCell, GameItemType itemType);
	void ClearTypeCell(GridCell& gridCell);
	bool IsAnythingInCell(GridCell& cell);

	struct GameGrid
	{
		std::vector<std::vector<GridCell>> cells;
	};

	void InitGameGrid(GameGrid& gameGrid);
	void ClearGameGrid(GameGrid& gameGrid);
	GridCell* GetRandomCell(GameGrid& gameGrid);
}

