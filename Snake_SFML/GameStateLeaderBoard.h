#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

namespace SnakeGame
{
	struct Game;

	struct GameStateLeaderBoardData
	{
		sf::Font font;

		MenuItem backItem;
		Menu menu;

		sf::Text leaderNumberText;
		sf::Text leaderNamesText;
		sf::Text leaderScoresText;
	};

	void InitGameStateLeaderBoard(GameStateLeaderBoardData& data, Game& game);
	void ShutdownGameStateLeaderBoard(GameStateLeaderBoardData& data);
	void HandleGameStateLeaderBoardWindowEvent(GameStateLeaderBoardData& data, Game& game, const sf::Event& event, const sf::Vector2i mousePosition);
	void UpdateGameStateLeaderBoard(GameStateLeaderBoardData& data);
	void DrawGameStateLeaderBoard(GameStateLeaderBoardData& data, sf::RenderWindow& window);
	void RunSelectedItem(GameStateLeaderBoardData& data, Game& game); 
}

