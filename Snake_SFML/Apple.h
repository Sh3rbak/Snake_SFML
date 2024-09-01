#pragma once
#include "SFML/Graphics.hpp"
#include "GameSettings.h"
#include "Math.h"

namespace SnakeGame
{
	struct Apple
	{
		PositionInGrid positionInGrid;
		Position position;
		sf::CircleShape shape;
		bool isEaten = false;
	};

	void InitApple(Apple& apple);
	void ResetAppleState(Apple& apple);
	void SetApplePosition(Apple& apple, Position position);
	void MarkAppleAsEaten(Apple& apple);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
}
