#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Math.h"

namespace SnakeGame
{
	enum class KindOfApple
	{
		UsualApple,
		BigApple,
		BoostApple,
		InvertedApple
	};

	struct Apple
	{
		PositionInGrid positionInGrid;
		Position position;
		sf::Sprite sprite;
		KindOfApple kind = KindOfApple::UsualApple;
		int duration = 0;
		bool isEaten = false;
	};

	void InitColorForSpriteOfUnusualApple(Apple& apple);
	void InitApple(Apple& apple, const sf::Texture& texture, KindOfApple kindOfApple = KindOfApple::UsualApple);
	void SetTransparencyOfAppleSprite(Apple& apple, const int degreeTransparency);
	void ResetAppleState(Apple& apple);
	void SetApplePosition(Apple& apple, const Position position, const PositionInGrid positionInGrid);
	void SetAppleDuration(Apple& apple, const int duration);
	int GetAppleDuration(const Apple& apple);
	void MarkAppleAsEaten(Apple& apple);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
	bool IsChanceAppearanceOfUnusualApple(const Apple& apple);
}
