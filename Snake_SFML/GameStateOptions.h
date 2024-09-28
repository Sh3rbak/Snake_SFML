#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

namespace SnakeGame
{
	struct Game;

	struct GameStateOptionsData
	{
		sf::Font font;

		MenuItem musicItem;
		MenuItem soundItem;
		MenuItem backItem;
		Menu menu;

		sf::Texture checkMarkTexture;
		sf::Texture crossMarkTexture;

		sf::RectangleShape fieldMarkSoundShape;
		sf::RectangleShape fieldMarkMusicShape;
	};

	void InitGameStateOptions(GameStateOptionsData& data);
	void ShutdownGameStateOptions(GameStateOptionsData& data);
	void HandleGameStateOptionsWindowEvent(GameStateOptionsData& data, Game& game, const sf::Event& event, const sf::Vector2i mousePosition);
	void UpdateGameStateOptions(GameStateOptionsData& data, const Game& game);
	void DrawGameStateOptions(GameStateOptionsData& data, sf::RenderWindow& window);
	void RunSelectedItem(GameStateOptionsData& data, Game& game);
	void RunSelectedItemByMouse(GameStateOptionsData& data, Game& game, const sf::Event& event, MenuItem& menuItem);
}
