#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Math.h"
#include <list>

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
		sf::Sprite sprite;
		SnakeDirection direction = SnakeDirection::Left;
	};

	struct Snake
	{
		std::list<std::shared_ptr<PartOfBody>> body;
	};

	void InitSnakeHead(Snake& snake, const sf::Texture& textureOfHead);
	void InitSnakePartOfBody(PartOfBody& partOfBody, const sf::Texture& textureOfBody);
	void PushPartOfBody(Snake& snake, const sf::Texture& textureOfBody);
	void ClearSnake(Snake& snake);
	void UpdateSnakeBody(Snake& snake);
	void SetSnakeHeadDirection(Snake& snake, const SnakeDirection direction);
	void SetSnakeHeadPosition(Snake& snake, const Position position, const PositionInGrid positionInGrid);
	PositionInGrid GetSnakeHeadPositionInGrid(Snake& snake);
	SnakeDirection GetSnakeHeadDirection(Snake& snake);
	std::vector<PositionInGrid> GetPositionSnake(Snake& snake);
	void DrawSnake(Snake& snake, sf::RenderWindow& window);
}
