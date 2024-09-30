#include "GameGrid.h"

namespace SnakeGame
{
	void ChangeTypeCell(GridCell& gridCell, GameItemType itemType)
	{
		gridCell.type = itemType;
	}

	bool IsAnythingInCell(const GridCell& cell)
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
				cell.positionInGrid = { i , j };
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
		for (auto row = gameGrid.cells.begin(); row != gameGrid.cells.end(); ++row)
		{
			for (auto cell = row->begin(); cell != row->end(); ++cell)
			{
				if (cell->type == GameItemType::None && &*cell != &nextCell)
				{
					positions.push_back(&(*cell));
				}
			}
		}

		if (positions.size() < 1)
		{
			return nullptr;
		}

		const int randPos = rand() % positions.size();
		return positions[randPos];
	}

	bool FindRandomFreeCell(GameGrid& grid, GridCell*& expactedFreeCell, GridCell& nextCellForSnake)
	{
		auto randomCell = GetRandomCell(grid);
		int tryingFind = 0;
		// find free cells
		while (IsAnythingInCell(*randomCell))
		{
			if (tryingFind > 10)
			{
				randomCell = FindEmptyCell(grid, nextCellForSnake);
				break;
			}
			randomCell = GetRandomCell(grid);
			++tryingFind;
		}

		if (randomCell == nullptr)
		{
			return false;
		}
		expactedFreeCell = randomCell;
		return true;
	}
}
