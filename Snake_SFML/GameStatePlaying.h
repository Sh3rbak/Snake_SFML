#pragma once
#include "SFML/Graphics.hpp"
#include "Apple.h"
#include "Snake.h"
#include "GameGrid.h"
#include "UI.h"
#include <list>

namespace SnakeGame
{
	struct Game;

	struct GameStatePlayingData
	{
		sf::Texture headSnakeTexture;
		sf::Texture bodySnakeTexture;
		sf::Texture appleTexture;

		Snake snake;
		Apple apple;
		GameGrid gameGrid;
		unsigned int numEatenApples = 0;
		float timeBetweenLoop = 0;
		SnakeDirection newDirection;

		sf::Font font;
		UI ui;
	};

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game);
	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game);
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event event, sf::Vector2i mousePosition);
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float deltaTime);
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window);
}
