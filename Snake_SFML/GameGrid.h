#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "GameSettings.h"
#include "Math.h"

namespace SnakeGame
{
	struct Snake;
	struct Apple;
	struct GridCell
	{
		Position position;
		Snake* snake = nullptr;
		Apple* apple = nullptr;
	};

	template <class T>
	void AddItemToCell(GridCell& gridCell, T& item);
	template <class T>
	void RemoteItemFromCell(GridCell& gridCell, T& item);

	struct GameGrid
	{
		std::unordered_map<int, std::unordered_map<int, GridCell>> cells;
	};

	void InitGameGrid(GameGrid& gameGrid);
	void ClearGameGrid(GameGrid& gameGrid);
}

