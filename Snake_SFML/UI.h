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
		sf::Text pauseButtonText;

		float timeAtBeginning = PAUSE_AT_BEGINNING;
		sf::Text timeAtBeginningText;

		sf::RectangleShape line;
	};

	void InitUI(UI& ui, const sf::Font font);
	void UpdatePauseTimeUI(UI& ui, const float deltaTime);
	void UpdateScoreUI(UI& ui, const int score);
	void DrawUI(UI& ui, sf::RenderWindow& window);
	void ReturnOriginalPauseTime(UI& ui);
}
