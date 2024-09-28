#include "Fence.h"

namespace SnakeGame
{
	void InitFence(Fence& fence, const sf::Texture& texture, const Direction direction)
	{
		fence.sprite.setTexture(texture);
		fence.sprite.setOrigin(GetItemOrigin(fence.sprite, { 0.5f, 0.5f }));
		fence.sprite.setScale(GetSpriteScale(fence.sprite, { CELL_SIZE, CELL_SIZE }));
		fence.direction = direction;
	}

	void SetPositionOfFence(Fence& fence, const Position position)
	{
		fence.position = position;
	}

	void DrawFence(Fence& fence, sf::RenderWindow& window)
	{
		fence.sprite.setPosition(fence.position);
		const sf::Vector2f spriteScale = (GetSpriteScale(fence.sprite, { CELL_SIZE, CELL_SIZE }));

		switch (fence.direction)
		{
		case SnakeGame::Direction::Left:
			fence.sprite.setScale(spriteScale.x, spriteScale.y);
			fence.sprite.setRotation(90.f);
			break;
		case SnakeGame::Direction::Up:
			fence.sprite.setScale(spriteScale.x, -spriteScale.y);
			fence.sprite.setRotation(0.f);
			break;
		case SnakeGame::Direction::Right:
			fence.sprite.setScale(spriteScale.x, spriteScale.y);
			fence.sprite.setRotation(-90.f);
			break;
		case SnakeGame::Direction::Down:
			fence.sprite.setScale(spriteScale.x, spriteScale.y);
			fence.sprite.setRotation(0.f);
			break;
		}
		window.draw(fence.sprite);
	}
}