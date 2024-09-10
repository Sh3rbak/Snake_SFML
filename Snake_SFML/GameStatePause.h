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
		MenuItem newGameItem;
		MenuItem goToMenuItem;
		Menu menu;

		sf::RectangleShape backround;
	};

	void InitGameStatePause(GameStatePauseData& data, Game& game);
	void ShutdownGameStatePause(GameStatePauseData& data);
	void HandleGameStatePauseWindowEvent(GameStatePauseData& data, Game& game, const sf::Event& event, sf::Vector2i mousePosition);
	void UpdateGameStatePause(GameStatePauseData& data, Game& game);
	void DrawGameStatePause(GameStatePauseData& data, Game& game, sf::RenderWindow& window);
	void RunSelectedItem(GameStatePauseData& data, Game& game);
}

