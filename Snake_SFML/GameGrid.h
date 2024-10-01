#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "GameSettings.h"
#include "Math.h"
#include "Fence.h"

namespace SnakeGame
{
	enum class GameItemType
	{
		None,
		Apple,
		Snake,
		Fence
	};

	struct GridCell
	{ 
		Position position;
		GameItemType type = GameItemType::None;
	};

	void ChangeTypeCell(GridCell& gridCell, GameItemType itemType);
	bool IsAnythingInCell(const GridCell& cell);

	struct GameGrid
	{
		std::vector<std::vector<GridCell>> cells;
	};

	void InitGameGrid(GameGrid& gameGrid);
	void ClearGameGrid(GameGrid& gameGrid);
	GridCell* GetRandomCell(GameGrid& gameGrid);
	GridCell* FindEmptyCell(GameGrid& gameGrid, const GridCell& nextCell);
	bool FindRandomFreeCell(GameGrid& grid, GridCell*& expactedFreeCell, GridCell& nextCellForSnake);
}

