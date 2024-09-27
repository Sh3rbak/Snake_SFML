#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Math.h"

namespace SnakeGame
{
	struct Apple
	{
		PositionInGrid positionInGrid;
		Position position;
		sf::Sprite sprite;
		bool isEaten = false;
	};

	void InitApple(Apple& apple, sf::Texture& texture);
	void ResetAppleState(Apple& apple);
	void SetApplePosition(Apple& apple, Position position);
	void MarkAppleAsEaten(Apple& apple);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
}
