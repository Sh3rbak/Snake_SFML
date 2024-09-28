#include "Apple.h"

namespace SnakeGame
{
	void InitApple(Apple& apple, const sf::Texture& texture)
	{
		apple.sprite.setTexture(texture);
		apple.sprite.setOrigin(GetItemOrigin(apple.sprite, { 0.5f, 0.5f }));
		apple.sprite.setScale(GetSpriteScale(apple.sprite, { APPLE_SIZE, APPLE_SIZE }));
	}

	void ResetAppleState(Apple& apple)
	{
		apple.isEaten = false;
	}

	void SetApplePosition(Apple& apple, const Position position)
	{
		apple.position = position;
	}

	void MarkAppleAsEaten(Apple& apple)
	{
		apple.isEaten = true;
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		if (apple.isEaten)
		{
			return;
		}

		apple.sprite.setPosition(apple.position);
		window.draw(apple.sprite);
	}
}