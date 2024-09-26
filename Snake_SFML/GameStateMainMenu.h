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
		MenuItem backFromDifficultyItem;
		MenuItem beginnerItem;
		MenuItem easyItem;
		MenuItem normalItem;
		MenuItem hardItem;
		MenuItem challengingItem;
		MenuItem optionsItem;
		MenuItem backFromOptionsItem;
		MenuItem leaderBoardItem;
		MenuItem backFromLeaberBoardItem;
		MenuItem exitGameItem;
		MenuItem noItem;
		MenuItem yesItem;

		Menu menu;
	};

	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void ShutdownGameStateMainMenu(GameStateMainMenuData& data);
	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event, sf::Vector2i mousePosition);
	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window);
	void RunSelectedItem(GameStateMainMenuData& data, Game& game);
}
