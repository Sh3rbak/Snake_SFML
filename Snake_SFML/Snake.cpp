#include "Snake.h"

namespace SnakeGame
{
	void InitSnakeHead(Snake& snake)
	{
		if(snake.body.size() > 0)
		{
			return;
		}
		snake.body.push_back(new PartOfBody);
		snake.body.back()->shape.setSize({ SNAKE_SIZE, SNAKE_SIZE });
		snake.body.back()->shape.setFillColor(sf::Color::Green);
		snake.body.back()->shape.setOrigin({ SNAKE_SIZE / 2.f, SNAKE_SIZE / 2.f });
	}

	void InitSnakePartOfBody(PartOfBody& partOfBody)
	{
		partOfBody.shape.setSize({ SNAKE_SIZE, SNAKE_SIZE });
		partOfBody.shape.setFillColor(sf::Color::Green);
		partOfBody.shape.setOrigin({ SNAKE_SIZE / 2.f, SNAKE_SIZE / 2.f });
	}

	void PushPartOfBody(Snake& snake)
	{
		if (snake.body.size() < 1)
		{
			return;
		}
		snake.body.push_back(new PartOfBody);

		InitSnakePartOfBody(*snake.body.back());
	}

	void ClearSnake(Snake& snake)
	{
		for (auto it : snake.body)
		{
			delete it;
		}
	}

	void UpdateSnakeBody(Snake& snake)
	{
		if (snake.body.size() < 2)
		{
			return;
		}
		PartOfBody* oldPartOfBody = snake.body.back();
		for (auto it = snake.body.rbegin(); it != snake.body.rend(); ++it)
		{
			oldPartOfBody->position = (*it)->position;
			oldPartOfBody->positionInGrid = (*it)->positionInGrid;
			oldPartOfBody->direction = (*it)->direction;
			oldPartOfBody = *it;
		}
	}

	void SetSnakeHeadDirection(Snake& snake, SnakeDirection direction)
	{
		if ((static_cast<int>(snake.body.front()->direction) % 2) == (static_cast<int>(direction) % 2))
		{
			return;
		}
		snake.body.front()->direction = direction;
	}

	void SetSnakeHeadPosition(Snake& snake, Position position, PositionInGrid positionInGrid)
	{
		snake.body.front()->position = position;
		snake.body.front()->positionInGrid = positionInGrid;
	}

	PositionInGrid GetSnakeHeadPositionInGrid(Snake& snake)
	{
		return snake.body.front()->positionInGrid;
	}

	SnakeDirection GetSnakeHeadDirection(Snake& snake)
	{
		return snake.body.front()->direction;
	}

	std::vector<PositionInGrid> GetPositionSnake(Snake& snake)
	{
		std::vector<PositionInGrid> snakeInGrid;
		for (auto it : snake.body)
		{
			snakeInGrid.push_back(it->positionInGrid);
		}
		return snakeInGrid;
	}

	void DrawSnake(Snake& snake, sf::RenderWindow& window)
	{
		for (auto it : snake.body)
		{
			it->shape.setPosition(it->position);
			window.draw(it->shape);
		}
	}
}