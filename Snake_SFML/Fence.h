#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Math.h"

namespace SnakeGame
{
	enum class Direction
	{
		Left,
		Up,
		Right,
		Down
	};

	struct Fence
	{
		Position position;
		sf::Sprite sprite;
		Direction direction = Direction::Down;

		Fence() : position({ 0, 0 }) {}
	};

	void InitFence(Fence& fence, sf::Texture& texture, const Direction direction);
	void SetPositionOfFence(Fence& fence, const Position position);
	void DrawFence(Fence& fence, sf::RenderWindow& window);
}
