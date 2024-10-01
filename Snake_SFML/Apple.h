#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Math.h"

namespace SnakeGame
{
	struct Apple
	{
		Position position;
		sf::Sprite sprite;
	};

	void InitApple(Apple& apple, const sf::Texture& texture);
	void SetApplePosition(Apple& apple, const Position position);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
}
