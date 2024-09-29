#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "GameSounds.h"
#include <unordered_map>

namespace SnakeGame
{
	enum class GameOptions : std::uint8_t
	{
		Sound = 1 << 0,
		Music = 1 << 1,

		Default = Sound | Music,
		Empty = 0
	};

	enum class GameDifficulty
	{
		Beginner,
		Easy,
		Normal,
		Hard,
		Challenge
	};

	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		Difficulty,
		GameMods,
		Options,
		LeaderBoard,
		GameOver,
		EnterName,
		Pause
	};

	struct GameState
	{
		GameStateType type = GameStateType::None;
		std::shared_ptr<void> data = nullptr;
		bool isExclusivelyVisible = false;
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	struct Game
	{
		std::vector<GameState> gameStateStack;
		GameStateChangeType gameStateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;

		GameOptions options = GameOptions::Default;
		GameDifficulty difficulty = GameDifficulty::Normal;
		bool isWinGame = false;
		int gameScore = 0;
		std::unordered_multimap<std::string, int> recordsTable;

		GameSounds sound;
	};

	void InitGame(Game& game);
	void HandleWindowEvents(Game& game, sf::RenderWindow& window);
	bool UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void ShutdownGame(Game& game);

	void PushGameState(Game& game, GameStateType stateType, bool isExclusivelyVisible);
	void PopGameState(Game& game);
	void SwitchGameState(Game& game, GameStateType stateType);

	void InitGameState(Game& game, GameState& state);
	void ShutdownGameState(Game& game, GameState& state);
	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event, sf::Vector2i mousePosition);
	void UpdateGameState(Game& game, GameState& state, float deltaTime);
	void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window);

	bool SerializeGame(const Game& game);
	bool DeserializeGame(Game& game);
}

