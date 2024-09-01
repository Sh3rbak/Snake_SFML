#include "Snake.h"

namespace SnakeGame
{
	void InitSnakeHead(Snake& snake)
	{
		auto head = std::make_shared<PartOfBody>();
		snake.head = head;
		snake.head->shape.setSize({ SNAKE_SIZE, SNAKE_SIZE });
		snake.head->shape.setFillColor(sf::Color::Green);
		snake.head->shape.setOrigin({ SNAKE_SIZE / 2.f, SNAKE_SIZE / 2.f });
	}

	void InitSnakePartOfBody(PartOfBody& partOfBody)
	{
		partOfBody.shape.setSize({ SNAKE_SIZE, SNAKE_SIZE });
		partOfBody.shape.setFillColor(sf::Color::Green);
		partOfBody.shape.setOrigin({ SNAKE_SIZE / 2.f, SNAKE_SIZE / 2.f });
	}

	void PushPartOfBody(Snake& snake)
	{
		auto newPartOfBody = std::make_shared<PartOfBody>();
		InitSnakePartOfBody(*newPartOfBody);
		std::shared_ptr<PartOfBody> partOfBoby = snake.head;
		while (partOfBoby->nextPartOfBody)
		{
			partOfBoby = partOfBoby->nextPartOfBody;
		}
		newPartOfBody->previousPartOfBody = partOfBoby;
		partOfBoby->nextPartOfBody = newPartOfBody;
	}

	void ClearCnake(Snake& snake)
	{
		std::shared_ptr<PartOfBody> partOfBoby = snake.head;
		std::shared_ptr<PartOfBody> oldPartOfBody;
		while (partOfBoby->nextPartOfBody)
		{
			partOfBoby->previousPartOfBody.reset();
			oldPartOfBody = partOfBoby;
			partOfBoby = partOfBoby->nextPartOfBody;
			oldPartOfBody->nextPartOfBody.reset();
		}
		snake.head.reset();
	}

	void UpdateSnakeBody(Snake& snake)
	{
		std::shared_ptr<PartOfBody> partOfBoby = snake.head;
		while (partOfBoby->nextPartOfBody)
		{
			partOfBoby = partOfBoby->nextPartOfBody;
		}
		while (partOfBoby->previousPartOfBody.lock())
		{
			partOfBoby->position = partOfBoby->previousPartOfBody.lock()->position;
			partOfBoby->positionInGrid = partOfBoby->previousPartOfBody.lock()->positionInGrid;
			partOfBoby->direction = partOfBoby->previousPartOfBody.lock()->direction;
			partOfBoby = partOfBoby->previousPartOfBody.lock();
		}
	}

	void SetSnakeHeadPosition(Snake& snake, Position position, PositionInGrid positionInGrid)
	{
		snake.head->position = position;
		snake.head->positionInGrid = positionInGrid;
	}

	std::vector<PositionInGrid> GetPositionSnake(Snake& snake)
	{
		std::vector<PositionInGrid> snakeInGrid;
		std::shared_ptr<PartOfBody> partOfBody = snake.head;
		while (partOfBody)
		{
			snakeInGrid.push_back(partOfBody->positionInGrid);
			partOfBody = partOfBody->nextPartOfBody;
		}
		return snakeInGrid;
	}

	void DrawSnake(Snake& snake, sf::RenderWindow& window)
	{
		std::shared_ptr<PartOfBody> partOfBoby = snake.head;
		while (partOfBoby)
		{
			partOfBoby->shape.setPosition(partOfBoby->position);
			window.draw(partOfBoby->shape);
			partOfBoby = partOfBoby->nextPartOfBody;
		}
	}
}