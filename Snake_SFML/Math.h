#pragma once
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	typedef sf::Vector2f Position;
	typedef sf::Vector2i PositionInGrid;

	sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, const sf::Vector2f& desiredSize);
	sf::Vector2f GetItemOrigin(const sf::Sprite& sprite, const sf::Vector2f& relativePosition);
	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);

	// Helper method for organizing text items
	enum class Orientation
	{
		Horizontal,
		Vertical
	};

	enum class Alignment
	{
		Min, // Left or Top
		Middle,
		Max // Right or Bottom
	};

	void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin);

	bool IsPointInRect(sf::Vector2f point, sf::Vector2f rectTL, sf::Vector2f rectBR);
	bool IsAllowSymbol(const sf::Event& event);

	template <class T>
	bool IsMouseOnItem(const sf::Vector2i mousePosition, T& item)
	{
		sf::FloatRect rectText = item.getGlobalBounds();
		return mousePosition.x > rectText.left && mousePosition.x < rectText.left + rectText.width &&
			mousePosition.y > rectText.top && mousePosition.y < rectText.top + rectText.height;
	}
}
