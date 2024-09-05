#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Math.h"

namespace SnakeGame
{
	struct UI
	{
		sf::Font font;

		sf::Text scoreText;
		sf::Text pauseText;

		sf::RectangleShape line;
	};

	void InitUI(UI& ui, sf::Font font);
	sf::FloatRect GetGlobalBoundsOfPauseButton(UI& ui);
	void UpdateUI(UI& ui, const int score);
	void DrawUI(UI& ui, sf::RenderWindow& window);
}
