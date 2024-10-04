#pragma once
#include <SFML/Graphics.hpp>
#include "Apple.h"
#include "Snake.h"
#include "Fence.h"
#include "GameGrid.h"
#include "UI.h"
#include <list>

namespace SnakeGame
{
	enum class AppleEffect : std::uint8_t
	{
		InvertedMoved = 1 << 0,
		BoostSpeed = 1 << 1,
		Empty = 0
	};

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
		Apple bigApple;
		Apple boostApple;
		Apple invertedApple;
		std::vector<Apple*> unusualApples;
		std::vector<std::shared_ptr<Fence>> fence;
		GameGrid gameGrid;

		unsigned int numEatenApples = 0;
		int pointPerApple = 0;
		float snakeSpeed = 0;
		SnakeDirection newDirection = SnakeDirection::Left;
		AppleEffect effect = AppleEffect::Empty;
		int durationBoostEffect = 0;
		int durationInvertedEffect = 0;

		bool isGameFinished = false;

		float timeAtBeginning = 0;
		float timeBetweenLoop = 0;

		sf::Font font;
		UI ui;
	};

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game);
	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game);
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event event, const sf::Vector2i mousePosition);
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float deltaTime);
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window);

	void SetFence(GameStatePlayingData& data, sf::Texture& fenceTexture, sf::Texture& fenceInCornerTexture);
	void SetNewDirection(GameStatePlayingData& data);
	void CalculateNextCellDependingOnDirection(GameStatePlayingData& data, PositionInGrid& positionInGrid);
	void UpdateCellsTypeWhenSnakeMoves(GameStatePlayingData& data, GridCell& newCell, PositionInGrid newPositionInGrid);
	void CalculateAppearanceOfUnusualApple(Apple& apple, GameGrid& gameGrid, GridCell& nextCellForSneak);
	void StopAppleEffects(GameStatePlayingData& data, AppleEffect effect);

	void InitDifficultyGame(GameStatePlayingData& data, Game& game);
}
