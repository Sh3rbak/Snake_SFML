#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Menu.h"

namespace SnakeGame
{
	struct Game;

	struct GameStateLeaderBoardData
	{
		MenuItem backItem;
	};

	void InitGameStateLeaderBoard(GameStateLeaderBoardData& data, Game& game);
	void ShutdownGameStateLeaderBoard(GameStateLeaderBoardData& data);
	void HandleGameStateLeaderBoardWindowEvent(GameStateLeaderBoardData& data, Game& game, const sf::Event& event, sf::Vector2i mousePosition);
	void UpdateGameStateLeaderBoard(GameStateLeaderBoardData& data, Game& game);
	void DrawGameStateLeaderBoard(GameStateLeaderBoardData& data, Game& game, sf::RenderWindow& window);
	/*void RunSelectedItem(GameStateLeaderBoardData& data, Game& game); */
}

