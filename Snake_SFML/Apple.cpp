#include "Apple.h"

namespace SnakeGame
{
	void InitApple(Apple& apple)
	{
		apple.shape.setRadius(APPLE_SIZE);
		apple.shape.setFillColor(sf::Color::Red);
		apple.shape.setOrigin({ APPLE_SIZE / 2.f, APPLE_SIZE / 2.f });
	}
	void ResetAppleState(Apple& apple)
	{
		apple.isEaten = false;
	}
	void MarkAppleAsEaten(Apple& apple)
	{
		apple.isEaten = true;
	}
	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		if (!apple.isEaten)
		{
			return;
		}

		apple.shape.setPosition(apple.position);
		window.draw(apple.shape);
	}
}