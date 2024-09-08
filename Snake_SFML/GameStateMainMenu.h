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
		MenuItem gameModsItem;
		MenuItem settingsItem;
		MenuItem leaderBoardItem;
		MenuItem exitGameItem;
		MenuItem yesItem;
		MenuItem noItem;

		Menu menu;
	};

	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void ShutdownGameStateMainMenu(GameStateMainMenuData& data);
	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event);
	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window);
}
