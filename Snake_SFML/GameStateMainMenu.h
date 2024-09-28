#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

namespace SnakeGame
{
	struct Game;

	struct GameStateMainMenuData
	{
		sf::Font fontTitle;
		sf::Font font;

		MenuItem startGameItem;
		MenuItem gameDifficultyItem;
		MenuItem optionsItem;
		MenuItem leaderBoardItem;
		MenuItem exitGameItem;
		MenuItem noItem;
		MenuItem yesItem;

		Menu menu;
	};

	void InitGameStateMainMenu(GameStateMainMenuData& data);
	void ShutdownGameStateMainMenu(GameStateMainMenuData& data);
	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event, const sf::Vector2i mousePosition);
	void UpdateGameStateMainMenu(GameStateMainMenuData& data);
	void DrawGameStateMainMenu(GameStateMainMenuData& data, sf::RenderWindow& window);
	void RunSelectedItem(GameStateMainMenuData& data, Game& game);
}
