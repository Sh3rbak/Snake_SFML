#pragma once
#include "SFML/Graphics.hpp"
#include "GameSettings.h"
#include "Math.h"

namespace SnakeGame
{
	enum class SnakeDirection
	{
		Left = 0,
		Up,
		Right,
		Down
	};

	struct Snake
	{
		Position position;
		PositionInGrid positionInGrid;
		sf::RectangleShape shape;
		SnakeDirection direction = SnakeDirection::Left;
		Snake* previousPartOfBody = nullptr;
	};

	void InitSnake(Snake& snake);
	void UpdateSnake(Snake& snake);
	void SetSnakePosition(Snake& snake, Position position, PositionInGrid positionInGrid);
	void DrawSnake(Snake& snake, sf::RenderWindow& window);
}
