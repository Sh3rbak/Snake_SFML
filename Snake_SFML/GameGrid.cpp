#include "GameGrid.h"

namespace SnakeGame
{
	template <class T>
	void AddItemToCell(GridCell& gridCell, T& item)
	{
		if (*T == Apple)
		{
			gridCell.apple = item;
		}
		else if (*T == Snake)
		{
			gridCell.snake = item;
		}
	}
	template<class T>
	void RemoteItemFromCell(GridCell& gridCell, T& item)
	{
		if (T == Apple)
		{
			gridCell.apple = nullptr;
		}
		else if (T == Snake)
		{
			gridCell.snake = nullptr;
		}
	}
	void InitGameGrid(GameGrid& gameGrid)
	{
		for (int i = 0; i < GRID_CELLS_HORIZONTAL; ++i)
		{
			for (int j = 0; j < GRID_CELLS_VERTICAL; ++j)
			{
				float positionX = static_cast<float>(CELL_SIZE * i + static_cast<float>(CELL_SIZE / 2));
				float positionY = static_cast<float>(CELL_SIZE * j + FIELD_ON_TOP_SCREEN + static_cast<float>(CELL_SIZE / 2));
				GridCell& cell = gameGrid.cells[i][j];
				cell.position = { positionX, positionY };
			}
		}
	}

	void ClearGameGrid(GameGrid& gameGrid)
	{
		gameGrid.cells.clear();
	}
}
