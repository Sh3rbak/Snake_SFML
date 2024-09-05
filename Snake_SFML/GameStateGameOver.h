#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Math.h"

namespace SnakeGame
{
	struct Game;

	struct GameStateGameOverData
	{
		sf::Font fontTitle;
		sf::Font font;

		Menu menu;
		MenuItem newGameItem;
		MenuItem goToMenuItem;
	};

	void InitGameStateGameOver(GameStateGameOverData& data, Game& game);
	void ShutdownGameStateGameOver(GameStateGameOverData& data);
	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event);
	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game);
	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window);
}
