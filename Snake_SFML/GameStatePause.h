#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

namespace SnakeGame
{
	struct Game;

	struct GameStatePauseData
	{
		sf::Font fontTitle;
		sf::Font font;

		MenuItem continueItem;
		MenuItem goToMenuItem;
		Menu menu;

		sf::RectangleShape backround;
	};

	void InitGameStatePause(GameStatePauseData& data);
	void ShutdownGameStatePause(GameStatePauseData& data);
	void HandleGameStatePauseWindowEvent(GameStatePauseData& data, Game& game, const sf::Event& event, const sf::Vector2i mousePosition);
	void UpdateGameStatePause(GameStatePauseData& data);
	void DrawGameStatePause(GameStatePauseData& data, sf::RenderWindow& window);
	void RunSelectedItem(GameStatePauseData& data, Game& game);
}

