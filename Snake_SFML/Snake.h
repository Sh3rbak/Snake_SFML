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

	struct PartOfBody
	{
		Position position;
		PositionInGrid positionInGrid;
		sf::RectangleShape shape;
		SnakeDirection direction = SnakeDirection::Left;
		std::shared_ptr<PartOfBody> nextPartOfBody;
		std::weak_ptr<PartOfBody> previousPartOfBody;

		PartOfBody() : position({0,0}), positionInGrid({0,0}){}
	};

	struct Snake
	{
		std::shared_ptr<PartOfBody> head = nullptr;
	};

	void InitSnakeHead(Snake& snake);
	void InitSnakePartOfBody(PartOfBody& partOfBody);
	void PushPartOfBody(Snake& snake);
	void ClearCnake(Snake& snake);
	void UpdateSnakeBody(Snake& snakeBody);
	void SetSnakeHeadPosition(Snake& snake, Position position, PositionInGrid positionInGrid);
	std::vector<PositionInGrid> GetPositionSnake(Snake& snake);
	void DrawSnake(Snake& snake, sf::RenderWindow& window);
}
