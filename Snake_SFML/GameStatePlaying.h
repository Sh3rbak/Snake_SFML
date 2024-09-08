#pragma once
#include "SFML/Graphics.hpp"
#include "Apple.h"
#include "Snake.h"
#include "Fence.h"
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
		sf::Texture fenceTexture;
		sf::Texture fenceInCornerTexture;

		Snake snake;
		Apple apple;
		std::vector<Fence*> fence;
		GameGrid gameGrid;

		unsigned int numEatenApples = 0;
		float timeBetweenLoop = 0;
		SnakeDirection newDirection = SnakeDirection::Left;

		sf::Font font;
		UI ui;
	};

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game);
	void ShutdownGameStatePlaying(GameStatePlayingData& data);
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event event, sf::Vector2i mousePosition);
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float deltaTime);
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window);

	void SetFence(GameStatePlayingData& data, sf::Texture& fenceTexture, sf::Texture& fenceInCornerTexture);
	void SetNewDirection(GameStatePlayingData& data);
	void CalculateNextCellDependingOnDirection(GameStatePlayingData& data, PositionInGrid& positionInGrid);
	void UpdateCellsTypeWhenSnakeMoves(GameStatePlayingData& data, GridCell& newCell, PositionInGrid newPositionInGrid);
}
