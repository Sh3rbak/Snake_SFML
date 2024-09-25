#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

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

		sf::Text finalScoreText;
		sf::Text recordsTableText;

		bool isRunGameStateEnterNameData = true;
	};

	void InitGameStateGameOver(GameStateGameOverData& data, Game& game);
	void ShutdownGameStateGameOver(GameStateGameOverData& data, Game& game);
	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event, sf::Vector2i mousePosition);
	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game);
	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window);
	void RunSelectedItem(GameStateGameOverData& data, Game& game);
}
