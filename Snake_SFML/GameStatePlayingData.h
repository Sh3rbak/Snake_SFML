#pragma once
#include "SFML/Graphics.hpp"
#include "Apple.h"
#include "Snake.h"
#include "GameGrid.h"
#include <list>

namespace SnakeGame
{
	struct Game;

	struct GameStatePlayingData
	{
		Snake snake;
		Apple apple;
		GameGrid gameGrid;
		int numEatenApples = 0;
		float timeBetweenLoop = 0;
		SnakeDirection newDirection;
	};

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game);
	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game);
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event event);
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float deltaTime);
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window);
}
