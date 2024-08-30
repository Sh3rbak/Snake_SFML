#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include "GameSettings.h"
#include "Math.h"

namespace SnakeGame
{
	struct Snake;
	struct GridCell
	{
		Position position;
		void* item = nullptr;
	};

	template <class T>
	void AddItemToCell(GridCell& gridCell, T& item)
	{
		if (gridCell.item != nullptr)
		{
			return;
		}
		gridCell.item = &item;
	}
	template <class T>
	void RemoteItemFromCell(GridCell& gridCell, T& item)
	{
		gridCell.item = nullptr;
	}

	struct GameGrid
	{
		std::vector<std::vector<GridCell>> cells;
		/*std::unordered_map<int, std::unordered_map<int, GridCell>> cells;*/
	};

	void InitGameGrid(GameGrid& gameGrid);
	void ClearGameGrid(GameGrid& gameGrid);
	GridCell GetRandomCell(GameGrid& gameGrid);
}

