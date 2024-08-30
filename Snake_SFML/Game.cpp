#include "Game.h"
#include "GameStatePlayingData.h"
#include <cassert>

namespace SnakeGame
{
	void InitGame(Game& game)
	{
		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
		SwitchGameState(game, GameStateType::Playing);
	}
	void HandleWindowEvents(Game& game, sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (game.gameStateStack.size() > 0)
			{
				HandleWindowEventGameState(game, game.gameStateStack.back(), event);
			}
		}
	}
	bool UpdateGame(Game& game, float deltaTime)
	{
		if (game.gameStateChangeType == GameStateChangeType::Switch)
		{
			while (game.gameStateStack.size() > 0)
			{
				/*ShutdownGameState(game, game.gameStateStack.back());*/
				game.gameStateStack.pop_back();
			}
		}
		else if (game.gameStateChangeType == GameStateChangeType::Pop)
		{
			if (game.gameStateStack.size() > 0)
			{
				/*ShutdownGameState(game, game.gameStateStack.back());*/
				game.gameStateStack.pop_back();
			}
		}

		if (game.gameStateChangeType != GameStateChangeType::None)
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

	/*void ShutdownGame(Game& game)
	{
		while (game.gameStateStack.size() > 0)
		{
			ShutdownGameState(game, game.gameStateStack.back());
			game.gameStateStack.pop_back();
		}

		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
	}*/

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
			break;
		case SnakeGame::GameStateType::Playing:
			state.data = std::make_shared<GameStatePlayingData>();
			InitGameStatePlaying(*(GameStatePlayingData*)state.data.get(), game);
			break;
		case SnakeGame::GameStateType::LeaderBoard:
			break;
		case SnakeGame::GameStateType::GameOver:
			break;
		case SnakeGame::GameStateType::ExitDialog:
			break;
		default:
			assert(false);
			break;
		}
	}

	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event)
	{
		switch (state.type)
		{
		case SnakeGame::GameStateType::MainMenu:
			break;
		case SnakeGame::GameStateType::Playing:
			HandleGameStatePlayingWindowEvent(*(GameStatePlayingData*)state.data.get(), game, event);
			break;
		case SnakeGame::GameStateType::LeaderBoard:
			break;
		case SnakeGame::GameStateType::GameOver:
			break;
		case SnakeGame::GameStateType::ExitDialog:
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
			break;
		case SnakeGame::GameStateType::Playing:
			UpdateGameStatePlaying(*(GameStatePlayingData*)state.data.get(), game, deltaTime);
			break;
		case SnakeGame::GameStateType::LeaderBoard:
			break;
		case SnakeGame::GameStateType::GameOver:
			break;
		case SnakeGame::GameStateType::ExitDialog:
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
			break;
		case SnakeGame::GameStateType::Playing:
			DrawGameStatePlaying(*(GameStatePlayingData*)state.data.get(), game, window);
			break;
		case SnakeGame::GameStateType::LeaderBoard:
			break;
		case SnakeGame::GameStateType::GameOver:
			break;
		case SnakeGame::GameStateType::ExitDialog:
			break;
		default:
			break;
		}
	}
}