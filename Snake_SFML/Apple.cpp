#include "Apple.h"

namespace SnakeGame
{
	void InitColorForSpriteOfUnusualApple(Apple& apple)
	{
		switch (apple.kind)
		{
		case SnakeGame::KindOfApple::BigApple:
			apple.sprite.setColor(sf::Color::Yellow);
			break;
		case SnakeGame::KindOfApple::BoostApple:
			apple.sprite.setColor(sf::Color(255, 100, 200));
			break;
		case SnakeGame::KindOfApple::InvertedApple:
			apple.sprite.setColor(sf::Color::Cyan);
			break;
		}
	}

	void InitApple(Apple& apple, const sf::Texture& texture, KindOfApple kindOfApple)
	{
		apple.sprite.setTexture(texture);
		apple.sprite.setOrigin(GetItemOrigin(apple.sprite, { 0.5f, 0.5f }));
		apple.kind = kindOfApple;
		if (apple.kind == KindOfApple::BigApple)
		{
			apple.sprite.setScale(GetSpriteScale(apple.sprite, { APPLE_SIZE * 1.3f, APPLE_SIZE * 1.3f }));
		}
		else
		{
			apple.sprite.setScale(GetSpriteScale(apple.sprite, { APPLE_SIZE, APPLE_SIZE }));
		}
		InitColorForSpriteOfUnusualApple(apple);
	}

	void SetTransparencyOfAppleSprite(Apple& apple, const int degreeTransparency)
	{
		apple.sprite.setColor(apple.sprite.getColor() - (sf::Color)(0, 0, 0, degreeTransparency));
	}

	void ResetAppleState(Apple& apple)
	{
		apple.isEaten = false;
		InitColorForSpriteOfUnusualApple(apple);
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
			if (chanceOfappearance > 995)
			{
				return true;
			}
			break;
		}
		return false;
	}
}