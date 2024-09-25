#pragma once
#include <string>

namespace SnakeGame
{
	const std::string RESOURCES_PATH = "Assets/";

	const int SCREEN_WIDHT = 1024;
	const int SCREEN_HEIGHT = 768;
	const int FIELD_ON_TOP_SCREEN = static_cast<int>(SCREEN_HEIGHT / 15);

	const float SNAKE_SIZE = 20.f;
	const float APPLE_SIZE = 20.f;

	const int CELL_SIZE = static_cast<int>(SNAKE_SIZE);
	const unsigned int GRID_CELLS_HORIZONTAL = unsigned(SCREEN_WIDHT / CELL_SIZE);
	const unsigned int GRID_CELLS_VERTICAL = unsigned((SCREEN_HEIGHT - FIELD_ON_TOP_SCREEN) / CELL_SIZE);

	const float HORIZONTAL_SPACE_FOR_GAME_FIELD = (SCREEN_WIDHT % GRID_CELLS_HORIZONTAL) / 2.f;
	const float VERTICAL_SPACE_FOR_GAME_FIELD = ((SCREEN_HEIGHT - FIELD_ON_TOP_SCREEN) % GRID_CELLS_VERTICAL) / 2.f;

	const float SNAKE_SPEED_BEGINNER = 0.8f; //in seconds
	const float SNAKE_SPEED_EASY = 0.6f;
	const float SNAKE_SPEED_NORMAL = 0.4f;
	const float SNAKE_SPEED_HARD = 0.2f;
	const float SNAKE_SPEED_CHALLENGE = 0.1f;

	const int NUM_POINTS_PER_APPLE_BEGINNER = 2;
	const int NUM_POINTS_PER_APPLE_EASY = 4;
	const int NUM_POINTS_PER_APPLE_NORMAL = 6;
	const int NUM_POINTS_PER_APPLE_HARD = 8;
	const int NUM_POINTS_PER_APPLE_CHALLENGE = 10;

	const int SNAKE_LEINGH_PER_APPLE = 2;

	const float PAUSE_AT_BEGINNING = 2.5f; //in seconds
	
	const int RECORDS_TABLE_SIZE_IN_GAME_OVER = 3;
	const int MAX_RECORDS_TABLE_SIZE = 5;
	const int MAX_SYMBOLS_IN_NAME = 3;
}