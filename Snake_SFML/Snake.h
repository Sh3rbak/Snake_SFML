#pragma once
#include "SFML/Graphics.hpp"
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

		PartOfBody() : position({ 0,0 }), positionInGrid({ 0,0 }) {}
	};

	struct Snake
	{
		std::list<PartOfBody*> body;
	};

	void InitSnakeHead(Snake& snake, sf::Texture& textureOfHead);
	void InitSnakePartOfBody(PartOfBody& partOfBody, sf::Texture& textureOfBody);
	void PushPartOfBody(Snake& snake, sf::Texture& textureOfBody);
	void ClearSnake(Snake& snake);
	void UpdateSnakeBody(Snake& snake);
	void SetSnakeHeadDirection(Snake& snake, SnakeDirection direction);
	void SetSnakeHeadPosition(Snake& snake, Position position, PositionInGrid positionInGrid);
	PositionInGrid GetSnakeHeadPositionInGrid(Snake& snake);
	SnakeDirection GetSnakeHeadDirection(Snake& snake);
	std::vector<PositionInGrid> GetPositionSnake(Snake& snake);
	void DrawSnake(Snake& snake, sf::RenderWindow& window);
}
