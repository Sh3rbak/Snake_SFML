#include "Snake.h"

namespace SnakeGame
{
	void InitSnake(Snake& snake)
	{
		snake.shape.setSize({ SNAKE_SIZE, SNAKE_SIZE });
		snake.shape.setFillColor(sf::Color::Green);
		snake.shape.setOrigin({ SNAKE_SIZE / 2.f, SNAKE_SIZE / 2.f});
	}
	void UpdateSnake(Snake& snake)
	{

	}
	void SetSnakePosition(Snake& snake, Position position, PositionInGrid positionInGrid)
	{
		snake.position = position;
		snake.positionInGrid = positionInGrid;
	}
	void DrawSnake(Snake& snake, sf::RenderWindow& window)
	{
		snake.shape.setPosition(snake.position);
		window.draw(snake.shape);
	}
}