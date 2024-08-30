#include "GameGrid.h"

namespace SnakeGame
{
	void InitGameGrid(GameGrid& gameGrid)
	{
		gameGrid.cells.resize(GRID_CELLS_HORIZONTAL);
		for (auto it = gameGrid.cells.begin(); it != gameGrid.cells.end(); ++it)
		{
			std::vector<GridCell>* verticalCells = &*it;
			verticalCells->resize(GRID_CELLS_VERTICAL);
		}
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

	GridCell GetRandomCell(GameGrid& gameGrid)
	{
		int randomCellX = rand() % GRID_CELLS_HORIZONTAL;
		int randomCellY = rand() % GRID_CELLS_VERTICAL;
		return gameGrid.cells[randomCellX][randomCellY];
	}
}
