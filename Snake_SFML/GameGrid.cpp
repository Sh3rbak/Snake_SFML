#include "GameGrid.h"

namespace SnakeGame
{
	void ChangeTypeCell(GridCell& gridCell, GameItemType itemType)
	{
		if (gridCell.type != GameItemType::None)
		{
			return;
		}
		gridCell.type = itemType;
	}

	void ClearTypeCell(GridCell& gridCell)
	{
		gridCell.type = GameItemType::None;
	}

	bool IsAnythingInCell(GridCell& cell)
	{
		if (cell.type != GameItemType::None)
		{
			return true;
		}
		return false;
	}

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

	GridCell* GetRandomCell(GameGrid& gameGrid)
	{
		int randomCellX = rand() % GRID_CELLS_HORIZONTAL;
		int randomCellY = rand() % GRID_CELLS_VERTICAL;
		return &gameGrid.cells[randomCellX][randomCellY];
	}

	GridCell* FindEmptyCell(GameGrid& gameGrid)
	{
		std::vector<GridCell*> positions;
		for (auto i = gameGrid.cells.begin(); i != gameGrid.cells.end(); ++i)
		{
			for (auto j = i->begin(); j != i->end(); ++j)
			{
				if (j->type == GameItemType::None)
				{
					positions.push_back(&(*j));
				}
			}
		}

		if (positions.size() <= 0)
		{
			return nullptr;
		}

		int randPos = rand() % positions.size() - 1;
		return positions[randPos];
	}
}
