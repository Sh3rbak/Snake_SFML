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
				const float positionX = static_cast<float>(CELL_SIZE * i + static_cast<float>(CELL_SIZE / 2) + HORIZONTAL_SPACE_FOR_GAME_FIELD);
				const float positionY = static_cast<float>(CELL_SIZE * j + FIELD_ON_TOP_SCREEN + static_cast<float>(CELL_SIZE / 2) + VERTICAL_SPACE_FOR_GAME_FIELD);
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
		const int randomCellX = rand() % GRID_CELLS_HORIZONTAL;
		const int randomCellY = rand() % GRID_CELLS_VERTICAL;
		return &gameGrid.cells[randomCellX][randomCellY];
	}

	GridCell* FindEmptyCell(GameGrid& gameGrid, const GridCell& nextCell)
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
		// erase cell where snake will be
		for (int i = 0; i < positions.size(); ++i)
		{
			if (positions[i] == &nextCell)
			{
				positions.erase(positions.begin() + i);
			}
		}

		if (positions.size() < 1)
		{
			return nullptr;
		}

		const int randPos = rand() % positions.size();
		return positions[randPos];
	}
}
