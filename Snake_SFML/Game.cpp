#include "Game.h"
#include "GameStateMainMenu.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStateEnterName.h"
#include "GameStatePause.h"
#include "GameStateLeaderBoard.h"
#include "GameStateOptions.h"
#include "GameStateDifficulty.h"
#include <cassert>
#include <fstream>

namespace SnakeGame
{
	void InitGame(Game& game)
	{
		DeserializeGame(game);

		InitGameSounds(game.sound);
		InitGameMusic(game.sound);

		game.options = GameOptions::Default;
		game.difficulty = GameDifficulty::Normal;

		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
		SwitchGameState(game, GameStateType::MainMenu);
	}

	void HandleWindowEvents(Game& game, sf::RenderWindow& window)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (game.gameStateStack.size() > 0)
			{
				HandleWindowEventGameState(game, game.gameStateStack.back(), event, mousePosition);
			}
		}
	}

	bool UpdateGame(Game& game, float deltaTime)
	{
		if (game.gameStateChangeType == GameStateChangeType::Switch)
		{
			while (game.gameStateStack.size() > 0)
			{
				ShutdownGameState(game, game.gameStateStack.back());
				game.gameStateStack.pop_back();
			}
		}
		else if (game.gameStateChangeType == GameStateChangeType::Pop)
		{
			if (game.gameStateStack.size() > 0)
			{
				ShutdownGameState(game, game.gameStateStack.back());
				game.gameStateStack.pop_back();
			}
		}

		if (game.pendingGameStateType != GameStateType::None)
		{
			game.gameStateStack.push_back({ game.pendingGameStateType, nullptr, game.pendingGameStateIsExclusivelyVisible });
			InitGameState(game, game.gameStateStack.back());
		}

		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;

		if (game.gameStateStack.size() > 0)
		{
			UpdateGameState(game, game.gameStateStack.back(), deltaTime);
			return true;
		}

		return false;
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		if (game.gameStateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = game.gameStateStack.rbegin(); it != game.gameStateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->isExclusivelyVisible)
				{
					break;
				}
			}
			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				DrawGameState(game, **it, window);
			}
		}
	}

	void ShutdownGame(Game& game)
	{
		while (game.gameStateStack.size() > 0)
		{
			ShutdownGameState(game, game.gameStateStack.back());
			game.gameStateStack.pop_back();
		}

		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
	}

	void PushGameState(Game& game, GameStateType stateType, bool isExclusivelyVisible)
	{
		game.pendingGameStateType = stateType;
		game.pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		game.gameStateChangeType = GameStateChangeType::Push;
	}

	void PopGameState(Game& game)
	{
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
		game.gameStateChangeType = GameStateChangeType::Pop;
	}

	void SwitchGameState(Game& game, GameStateType stateType)
	{
		game.pendingGameStateType = stateType;
		game.pendingGameStateIsExclusivelyVisible = false;
		game.gameStateChangeType = GameStateChangeType::Switch;
	}

	void InitGameState(Game& game, GameState& state)
	{
		switch (state.type)
		{
		case SnakeGame::GameStateType::MainMenu:
			state.data = std::make_shared<GameStateMainMenuData>();
			InitGameStateMainMenu(*(GameStateMainMenuData*)state.data.get());
			break;
		case SnakeGame::GameStateType::Playing:
			state.data = std::make_shared<GameStatePlayingData>();
			InitGameStatePlaying(*(GameStatePlayingData*)state.data.get(), game);
			break;
		case SnakeGame::GameStateType::Difficulty:
			state.data = std::make_shared<GameStateDifficultyData>();
			InitGameStateDifficulty(*(GameStateDifficultyData*)state.data.get());
			break;
		case SnakeGame::GameStateType::LeaderBoard:
			state.data = std::make_shared<GameStateLeaderBoardData>();
			InitGameStateLeaderBoard(*(GameStateLeaderBoardData*)state.data.get(), game);
			break;
		case SnakeGame::GameStateType::Options:
			state.data = std::make_shared<GameStateOptionsData>();
			InitGameStateOptions(*(GameStateOptionsData*)state.data.get());
			break;
		case SnakeGame::GameStateType::GameOver:
			state.data = std::make_shared<GameStateGameOverData>();
			InitGameStateGameOver(*(GameStateGameOverData*)state.data.get(), game);
			break;
		case SnakeGame::GameStateType::EnterName:
			state.data = std::make_shared<GameStateEnterNameData>();
			InitGameStateEnterName(*(GameStateEnterNameData*)state.data.get(), game);
			break;
		case SnakeGame::GameStateType::Pause:
			state.data = std::make_shared<GameStatePauseData>();
			InitGameStatePause(*(GameStatePauseData*)state.data.get());
			break;
		default:
			assert(false);
			break;
		}
	}

	void ShutdownGameState(Game& game, GameState& state)
	{
		switch (state.type)
		{
		case SnakeGame::GameStateType::MainMenu:
			ShutdownGameStateMainMenu(*(GameStateMainMenuData*)state.data.get());
			break;
		case SnakeGame::GameStateType::Playing:
			ShutdownGameStatePlaying(*(GameStatePlayingData*)state.data.get(), game);
			break;
		case SnakeGame::GameStateType::Difficulty:
			ShutdownGameStateDifficulty(*(GameStateDifficultyData*)state.data.get());
			break;
		case SnakeGame::GameStateType::LeaderBoard:
			ShutdownGameStateLeaderBoard(*(GameStateLeaderBoardData*)state.data.get());
			break;
		case SnakeGame::GameStateType::Options:
			ShutdownGameStateOptions(*(GameStateOptionsData*)state.data.get());
			break;
		case SnakeGame::GameStateType::GameOver:
			ShutdownGameStateGameOver(*(GameStateGameOverData*)state.data.get());
			break;
		case SnakeGame::GameStateType::EnterName:
			ShutdownGameStateEnterName(*(GameStateEnterNameData*)state.data.get(), game);
			break;
		case SnakeGame::GameStateType::Pause:
			ShutdownGameStatePause(*(GameStatePauseData*)state.data.get());
			break;
		default:
			assert(false);
			break;
		}
	}

	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event, sf::Vector2i mousePosition)
	{
		switch (state.type)
		{
		case SnakeGame::GameStateType::MainMenu:
			HandleGameStateMainMenuWindowEvent(*(GameStateMainMenuData*)state.data.get(), game, event, mousePosition);
			break;
		case SnakeGame::GameStateType::Playing:
			HandleGameStatePlayingWindowEvent(*(GameStatePlayingData*)state.data.get(), game, event, mousePosition);
			break;
		case SnakeGame::GameStateType::Difficulty:
			HandleGameStateDifficultyWindowEvent(*(GameStateDifficultyData*)state.data.get(), game, event, mousePosition);
			break;
		case SnakeGame::GameStateType::LeaderBoard:
			HandleGameStateLeaderBoardWindowEvent(*(GameStateLeaderBoardData*)state.data.get(), game, event, mousePosition);
			break;
		case SnakeGame::GameStateType::Options:
			HandleGameStateOptionsWindowEvent(*(GameStateOptionsData*)state.data.get(), game, event, mousePosition);
			break;
		case SnakeGame::GameStateType::GameOver:
			HandleGameStateGameOverWindowEvent(*(GameStateGameOverData*)state.data.get(), game, event, mousePosition);
			break;
		case SnakeGame::GameStateType::EnterName:
			HandleGameStateEnterNameWindowEvent(*(GameStateEnterNameData*)state.data.get(), game, event, mousePosition);
			break;
		case SnakeGame::GameStateType::Pause:
			HandleGameStatePauseWindowEvent(*(GameStatePauseData*)state.data.get(), game, event, mousePosition);
			break;
		default:
			assert(false);
			break;
		}
	}

	void UpdateGameState(Game& game, GameState& state, float deltaTime)
	{
		switch (state.type)
		{
		case SnakeGame::GameStateType::MainMenu:
			UpdateGameStateMainMenu(*(GameStateMainMenuData*)state.data.get());
			break;
		case SnakeGame::GameStateType::Playing:
			UpdateGameStatePlaying(*(GameStatePlayingData*)state.data.get(), game, deltaTime);
			break;
		case SnakeGame::GameStateType::Difficulty:
			UpdateGameStateDifficulty(*(GameStateDifficultyData*)state.data.get(), game);
			break;
		case SnakeGame::GameStateType::LeaderBoard:
			UpdateGameStateLeaderBoard(*(GameStateLeaderBoardData*)state.data.get());
			break;
		case SnakeGame::GameStateType::Options:
			UpdateGameStateOptions(*(GameStateOptionsData*)state.data.get(), game);
			break;
		case SnakeGame::GameStateType::GameOver:
			UpdateGameStateGameOver(*(GameStateGameOverData*)state.data.get(), game);
			break;
		case SnakeGame::GameStateType::EnterName:
			UpdateGameStateEnterName(*(GameStateEnterNameData*)state.data.get());
			break;
		case SnakeGame::GameStateType::Pause:
			UpdateGameStatePause(*(GameStatePauseData*)state.data.get());
			break;
		default:
			assert(false);
			break;
		}
	}

	void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window)
	{
		switch (state.type)
		{
		case SnakeGame::GameStateType::MainMenu:
			DrawGameStateMainMenu(*(GameStateMainMenuData*)state.data.get(), window);
			break;
		case SnakeGame::GameStateType::Playing:
			DrawGameStatePlaying(*(GameStatePlayingData*)state.data.get(), game, window);
			break;
		case SnakeGame::GameStateType::Difficulty:
			DrawGameStateDifficulty(*(GameStateDifficultyData*)state.data.get(), game, window);
			break;
		case SnakeGame::GameStateType::LeaderBoard:
			DrawGameStateLeaderBoard(*(GameStateLeaderBoardData*)state.data.get(), window);
			break;
		case SnakeGame::GameStateType::Options:
			DrawGameStateOptions(*(GameStateOptionsData*)state.data.get(), window);
			break;
		case SnakeGame::GameStateType::GameOver:
			DrawGameStateGameOver(*(GameStateGameOverData*)state.data.get(), window);
			break;
		case SnakeGame::GameStateType::EnterName:
			DrawGameStateEnterName(*(GameStateEnterNameData*)state.data.get(), window);
			break;
		case SnakeGame::GameStateType::Pause:
			DrawGameStatePause(*(GameStatePauseData*)state.data.get(), window);
			break;
		default:
			assert(false);
			break;
		}
	}
	bool SerializeGame(const Game& game)
	{
		std::ofstream file(RECORDS_PATH + "RECORDS_TABLE_FILE");
		if (file.is_open())
		{
			for (const auto& record : game.recordsTable)
			{
				file << record.first << " " << record.second << std::endl;
			}
			file.close();
			return true;
		}
		return false;
	}
	bool DeserializeGame(Game& game)
	{
		std::ifstream file(RECORDS_PATH + "RECORDS_TABLE_FILE");
		if (file.is_open())
		{
			std::string name;
			int score;
			while (file >> name >> score)
			{
				game.recordsTable[name] = score;
			}
			file.close();
			return true;
		}
		return false;
	}
}