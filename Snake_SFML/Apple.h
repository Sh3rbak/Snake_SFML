#pragma once
#include "SFML/Graphics.hpp"
#include "GameSettings.h"
#include "Math.h"

namespace SnakeGame
{
	struct GridCell;

	struct Apple
	{
		Position position;
		sf::CircleShape shape;
		bool isEaten = false;
		GridCell* cell = nullptr;
	};

	void InitApple(Apple& apple);
	void ResetAppleState(Apple& apple);
	void MarkAppleAsEaten(Apple& apple);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
}
