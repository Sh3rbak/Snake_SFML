#include "Snake.h"

namespace SnakeGame
{
	void InitSnakeHead(Snake& snake, const sf::Texture& textureOfHead)
	{
		if(snake.body.size() > 0)
		{
			return;
		}
		snake.body.push_back(std::make_shared<PartOfBody>());
		snake.body.back()->sprite.setTexture(textureOfHead);
		snake.body.back()->sprite.setOrigin(GetItemOrigin(snake.body.back()->sprite, { 0.5f, 0.5f }));
		snake.body.back()->sprite.setScale(GetSpriteScale(snake.body.back()->sprite, { SNAKE_SIZE, SNAKE_SIZE }));
	}

	void InitSnakePartOfBody(PartOfBody& partOfBody, const sf::Texture& textureOfBody)
	{
		partOfBody.sprite.setTexture(textureOfBody);
		partOfBody.sprite.setOrigin(GetItemOrigin(partOfBody.sprite, { 0.5f, 0.5f }));
		partOfBody.sprite.setScale(GetSpriteScale(partOfBody.sprite, { SNAKE_SIZE, SNAKE_SIZE }));
	}

	void PushPartOfBody(Snake& snake, const sf::Texture& textureOfBody)
	{
		if (snake.body.size() < 1)
		{
			return;
		}
		snake.body.push_back(std::make_shared<PartOfBody>());
		InitSnakePartOfBody(*snake.body.back(), textureOfBody);
	}

	void ClearSnake(Snake& snake)
	{
		snake.body.clear();
	}

	void UpdateSnakeBody(Snake& snake)
	{
		if (snake.body.size() < 2)
		{
			return;
		}
		// each part takes the parameters of the previous one
		std::shared_ptr<PartOfBody> oldPartOfBody = snake.body.back();
		for (auto it = snake.body.rbegin(); it != snake.body.rend(); ++it)
		{
			oldPartOfBody->position = (*it)->position;
			oldPartOfBody->positionInGrid = (*it)->positionInGrid;
			oldPartOfBody->direction = (*it)->direction;
			oldPartOfBody = *it;
		}
	}

	void SetSnakeHeadDirection(Snake& snake, const SnakeDirection direction)
	{
		//the head should't move in the opposite direction at once
		if ((static_cast<int>(snake.body.front()->direction) % 2) == (static_cast<int>(direction) % 2))
		{
			return;
		}
		snake.body.front()->direction = direction;
	}

	void SetSnakeHeadPosition(Snake& snake, const Position position, const PositionInGrid positionInGrid)
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
		for (auto& it : snake.body)
		{
			snakeInGrid.push_back(it->positionInGrid);
		}
		return snakeInGrid;
	}

	void DrawSnake(Snake& snake, sf::RenderWindow& window)
	{
		for (auto& it : snake.body)
		{
			const sf::Vector2f spriteScale = (GetSpriteScale(it->sprite, {SNAKE_SIZE, SNAKE_SIZE}));

			switch (it->direction)
			{
			case SnakeDirection::Up:
			{
				it->sprite.setScale(spriteScale.x, spriteScale.y);
				it->sprite.setRotation(-90.f);
				break;
			}
			case SnakeDirection::Right:
			{
				it->sprite.setScale(spriteScale.x, spriteScale.y);
				it->sprite.setRotation(0.f);
				break;
			}
			case SnakeDirection::Down:
			{
				it->sprite.setScale(spriteScale.x, spriteScale.y);
				it->sprite.setRotation(90.f);
				break;
			}
			case SnakeDirection::Left:
			{
				it->sprite.setScale(-spriteScale.x, spriteScale.y);
				it->sprite.setRotation(0.f);
				break;
			}
			}

			it->sprite.setPosition(it->position);
			window.draw(it->sprite);
		}
	}
}