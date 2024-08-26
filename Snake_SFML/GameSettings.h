#pragma once
#include <string>

namespace SnakeGame
{
	const std::string RESOURCES_PATH = "Assets/";

	const int SCREEN_WIDHT = 1024;
	const int SCREEN_HEIGHT = 768;
	const int FIELD_ON_TOP_SCREEN = 60;

	const float SNAKE_SIZE = 20.f;
	const int SNAKE_SPEED = 150;
	const float APPLE_SIZE = 20.f;

	const int CELL_SIZE = APPLE_SIZE;
	const unsigned int GRID_CELLS_HORIZONTAL = unsigned(SCREEN_WIDHT / APPLE_SIZE);
	const unsigned int GRID_CELLS_VERTICAL = unsigned((SCREEN_HEIGHT - FIELD_ON_TOP_SCREEN) / APPLE_SIZE);
	const int GAME_FIELD_WIDHT = CELL_SIZE * GRID_CELLS_HORIZONTAL;
	const int GAME_FIELD_HEIGHT = (CELL_SIZE * GRID_CELLS_VERTICAL);
}