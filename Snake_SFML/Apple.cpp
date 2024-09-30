#include "Apple.h"

namespace SnakeGame
{
	void InitApple(Apple& apple, const sf::Texture& texture, KindOfApple kindOfApple)
	{
		apple.sprite.setTexture(texture);
		apple.sprite.setOrigin(GetItemOrigin(apple.sprite, { 0.5f, 0.5f }));
		switch (kindOfApple)
		{
		case SnakeGame::KindOfApple::UsualApple:
			apple.sprite.setScale(GetSpriteScale(apple.sprite, { APPLE_SIZE, APPLE_SIZE }));
			apple.kind = KindOfApple::UsualApple;
			apple.isEaten = false;
			break;
		case SnakeGame::KindOfApple::BigApple:
			apple.sprite.setScale(GetSpriteScale(apple.sprite, { APPLE_SIZE * 1.3f, APPLE_SIZE * 1.3f}));
			apple.sprite.setColor(sf::Color::Yellow);
			apple.kind = KindOfApple::BigApple;
			break;
		case SnakeGame::KindOfApple::BoostApple:
			apple.sprite.setScale(GetSpriteScale(apple.sprite, { APPLE_SIZE, APPLE_SIZE }));
			apple.sprite.setColor(sf::Color( 255, 100, 200));
			apple.kind = KindOfApple::BoostApple;
			break;
		case SnakeGame::KindOfApple::InvertedApple:
			apple.sprite.setScale(GetSpriteScale(apple.sprite, { APPLE_SIZE, APPLE_SIZE }));
			apple.sprite.setColor(sf::Color::Cyan);
			apple.kind = KindOfApple::InvertedApple;
			break;
		}
	}

	void ResetAppleState(Apple& apple)
	{
		apple.isEaten = false;
	}

	void SetApplePosition(Apple& apple, const Position position, const PositionInGrid positionInGrid)
	{
		apple.positionInGrid = positionInGrid;
		apple.position = position;
	}

	void SetAppleDuration(Apple& apple, const int duration)
	{
		apple.duration = duration;
	}

	int GetAppleDuration(Apple& apple)
	{
		return apple.duration;
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

	bool IsChanceAppearanceOfUnusualApple(const Apple& apple)
	{
		const unsigned int chanceOfappearance = rand() % 1000;
		switch (apple.kind)
		{
		case SnakeGame::KindOfApple::BigApple:
			if (chanceOfappearance < 10)
			{
				return true;
			}
			break;
		case SnakeGame::KindOfApple::BoostApple:
			if (chanceOfappearance > 500 && chanceOfappearance < 505)
			{
				return true;
			}
			break;
		case SnakeGame::KindOfApple::InvertedApple:
			if (chanceOfappearance > 900)
			{
				return true;
			}
			break;
		}
		return false;
	}
}