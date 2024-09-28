#include "GameStatePlaying.h"
#include <cassert>
#include "Game.h"

namespace SnakeGame
{
	void SetDifficultyGame(GameStatePlayingData& data, Game& game)
	{
		switch (game.difficulty)
		{
		case SnakeGame::GameDifficulty::Beginner:
			data.snakeSpeed = SNAKE_SPEED_BEGINNER;
			data.pointPerApple = NUM_POINTS_PER_APPLE_BEGINNER;
			break;
		case SnakeGame::GameDifficulty::Easy:
			data.snakeSpeed = SNAKE_SPEED_EASY;
			data.pointPerApple = NUM_POINTS_PER_APPLE_EASY;
			break;
		case SnakeGame::GameDifficulty::Normal:
			data.snakeSpeed = SNAKE_SPEED_NORMAL;
			data.pointPerApple = NUM_POINTS_PER_APPLE_NORMAL;
			break;
		case SnakeGame::GameDifficulty::Hard:
			data.snakeSpeed = SNAKE_SPEED_HARD;
			data.pointPerApple = NUM_POINTS_PER_APPLE_HARD;
			break;
		case SnakeGame::GameDifficulty::Challenge:
			data.snakeSpeed = SNAKE_SPEED_CHALLENGE;
			data.pointPerApple = NUM_POINTS_PER_APPLE_CHALLENGE;
			break;
		}
	}

	void SetFence(GameStatePlayingData& data, sf::Texture& fenceTexture, sf::Texture& fenceInCornerTexture)
	{
		auto setFence = [&data](GridCell& cell, sf::Texture& texture, Direction direction,
			GameItemType type = GameItemType::Fence)
			{
				cell.type = type;
				data.fence.push_back(std::make_shared<Fence>());
				InitFence(*data.fence.back(), texture, direction);
				SetPositionOfFence(*data.fence.back(), cell.position);
			};

		std::vector<GridCell>* rowCells = &data.gameGrid.cells.front();
		for (auto it = rowCells->begin() + 1; it != rowCells->end() - 1; ++it)
		{
			setFence(*it, fenceTexture, Direction::Right);
		}

		rowCells = &data.gameGrid.cells.back();
		for (auto it = rowCells->begin() + 1; it != rowCells->end() - 1; ++it)
		{
			setFence(*it, fenceTexture, Direction::Left);
		}

		for (auto it = data.gameGrid.cells.begin(); it != data.gameGrid.cells.end(); ++it)
		{
			setFence(it->front(), fenceTexture, Direction::Down);
			setFence(it->back(), fenceTexture, Direction::Up);
		}

		GridCell* cellWithFence = &data.gameGrid.cells.begin()->front();
		setFence(*cellWithFence, fenceInCornerTexture, Direction::Down);

		cellWithFence = &data.gameGrid.cells.begin()->back();
		setFence(*cellWithFence, fenceInCornerTexture, Direction::Down);

		cellWithFence = &data.gameGrid.cells.back().front();
		setFence(*cellWithFence, fenceInCornerTexture, Direction::Down);

		cellWithFence = &data.gameGrid.cells.back().back();
		setFence(*cellWithFence, fenceInCornerTexture, Direction::Down);
	}

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		SetDifficultyGame(data, game);
		game.isWinGame = false;

		assert(data.headSnakeTexture.loadFromFile(RESOURCES_PATH + "Textures/SnakeHead.png"));
		assert(data.bodySnakeTexture.loadFromFile(RESOURCES_PATH + "Textures/SnakeBody.png"));
		assert(data.appleTexture.loadFromFile(RESOURCES_PATH + "Textures/Apple.png"));

		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Retro-Gaming.ttf"));

		assert(data.fenceTexture.loadFromFile(RESOURCES_PATH + "Textures/fence.png", sf::IntRect(8, 0, 8, 8)));
		assert(data.fenceInCornerTexture.loadFromFile(RESOURCES_PATH + "Textures/fence.png", sf::IntRect(0, 0, 8, 8)));

		InitGameGrid(data.gameGrid);
		InitSnakeHead(data.snake, data.headSnakeTexture);
		InitApple(data.apple, data.appleTexture);
		InitUI(data.ui, data.font);

		data.numEatenApples = 0;

		const int perimeter = (GRID_CELLS_VERTICAL * 2) + ((GRID_CELLS_HORIZONTAL - 2) * 2);
		data.fence.reserve(perimeter);
		SetFence(data, data.fenceTexture, data.fenceInCornerTexture);

		PositionInGrid positionCenterGrid = { GRID_CELLS_HORIZONTAL / 2, GRID_CELLS_VERTICAL / 2 };
		GridCell* centerGrid = &data.gameGrid.cells[positionCenterGrid.x][positionCenterGrid.y];
		SetSnakeHeadPosition(data.snake, centerGrid->position, { positionCenterGrid.x, positionCenterGrid.y });
		ChangeTypeCell(*centerGrid, GameItemType::Snake);

		GridCell* randomCell = GetRandomCell(data.gameGrid);
		while (IsAnythingInCell(*randomCell))
		{
			randomCell = GetRandomCell(data.gameGrid);
		}
		SetApplePosition(data.apple, randomCell->position);
		ChangeTypeCell(*randomCell, GameItemType::Apple);

		PlayGameMusic(game.sound, static_cast<uint8_t>(game.options));
	}

	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		game.gameScore = data.numEatenApples;
		ClearGameGrid(data.gameGrid);
		ClearSnake(data.snake);
		data.fence.clear();
		StopGameMusic(game.sound);
	}

	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event event, const sf::Vector2i mousePosition)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::P)
			{
				PushGameState(game, GameStateType::Pause, false);
				data.timeAtBeginning = 0;
				ReturnOriginalPauseTime(data.ui);
			}
		}
		if (IsMouseOnItem(mousePosition, data.ui.pauseButtonText))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				PushGameState(game, GameStateType::Pause, false);
				data.timeAtBeginning = 0;
				ReturnOriginalPauseTime(data.ui);
			}
		}
	}

	void SetNewDirection(GameStatePlayingData& data)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			data.newDirection = SnakeDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			data.newDirection = SnakeDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			data.newDirection = SnakeDirection::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			data.newDirection = SnakeDirection::Left;
		}
	}

	void CalculateNextCellDependingOnDirection(GameStatePlayingData& data, PositionInGrid& positionInGrid)
	{
		switch (GetSnakeHeadDirection(data.snake))
		{
		case SnakeDirection::Left:
		{
			--positionInGrid.x;
			break;
		}
		case SnakeDirection::Up:
		{
			--positionInGrid.y;
			break;
		}
		case SnakeDirection::Right:
		{
			++positionInGrid.x;
			break;
		}
		case SnakeDirection::Down:
		{
			++positionInGrid.y;
			break;
		}
		}
	}

	void UpdateCellsTypeWhenSnakeMoves(GameStatePlayingData& data, GridCell& newCell, PositionInGrid newPositionInGrid)
	{
		//clearing type of cells
		std::vector<PositionInGrid> positionSnakeInGrid = GetPositionSnake(data.snake);
		for (auto it = positionSnakeInGrid.begin(); it != positionSnakeInGrid.end(); ++it)
		{
			ClearTypeCell(data.gameGrid.cells[it->x][it->y]);
		}

		UpdateSnakeBody(data.snake);
		SetSnakeHeadPosition(data.snake, newCell.position, { newPositionInGrid.x, newPositionInGrid.y });

		//filling in type of cells with Snake
		positionSnakeInGrid = GetPositionSnake(data.snake);
		for (auto it = positionSnakeInGrid.begin(); it != positionSnakeInGrid.end(); ++it)
		{
			ChangeTypeCell(data.gameGrid.cells[it->x][it->y], GameItemType::Snake);
		}
	}

	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float deltaTime)
	{		
		if (data.timeAtBeginning < PAUSE_AT_BEGINNING)
		{
			UpdatePauseTimeUI(data.ui, deltaTime);
			data.timeAtBeginning += deltaTime;
			return;
		}

		SetNewDirection(data);

		// delay between movement
		data.timeBetweenLoop += deltaTime;
		if(data.timeBetweenLoop < data.snakeSpeed)
		{
			return;
		}
		data.timeBetweenLoop = 0;
		
		SetSnakeHeadDirection(data.snake, data.newDirection);

		//calculate the next cell
		PositionInGrid currectPositionInGrid = GetSnakeHeadPositionInGrid(data.snake);
		GridCell* currectCell = &data.gameGrid.cells[currectPositionInGrid.x][currectPositionInGrid.y];

		CalculateNextCellDependingOnDirection(data, currectPositionInGrid);

		currectCell = &data.gameGrid.cells[currectPositionInGrid.x][currectPositionInGrid.y];

		if (IsAnythingInCell(*currectCell))
		{
			switch (currectCell->type)
			{
			case SnakeGame::GameItemType::Apple:
			{
				ClearTypeCell(*currectCell);
				auto randomCell = GetRandomCell(data.gameGrid);
				int tryingFind = 0;
				// find free cells
				while (IsAnythingInCell(*randomCell))
				{
					if (tryingFind > 10)
					{
						randomCell = FindEmptyCell(data.gameGrid, *currectCell);
						break;
					}
					randomCell = GetRandomCell(data.gameGrid);
					++tryingFind;
				}
				// if run out of free cells
				if (randomCell == nullptr)
				{
					data.isGameFinished = true;
					game.isWinGame = true;
					return;
				}
				SetApplePosition(data.apple, randomCell->position);
				ChangeTypeCell(*randomCell, GameItemType::Apple);
				for (int i = 0; i < SNAKE_LEINGH_PER_APPLE; ++i)
				{
					PushPartOfBody(data.snake, data.bodySnakeTexture);
				}
				data.numEatenApples += data.pointPerApple;
				break;
			}
			case SnakeGame::GameItemType::Snake:
			case SnakeGame::GameItemType::Fence:
			{
				data.isGameFinished = true;
				break;
			}
			}
			PlayGameSounds(game.sound, static_cast<uint8_t>(game.options), SoundOption::Hit);
		}

		//checking collision with board
		const bool isOutsideField = currectPositionInGrid.x < 0 || currectPositionInGrid.x >= GRID_CELLS_HORIZONTAL ||
			                  currectPositionInGrid.y < 0 || currectPositionInGrid.y >= GRID_CELLS_VERTICAL;
		if (isOutsideField || data.isGameFinished)
		{
			SwitchGameState(game, GameStateType::GameOver);
			return;
		}

		UpdateCellsTypeWhenSnakeMoves(data, *currectCell, currectPositionInGrid);

		UpdateScoreUI(data.ui, data.numEatenApples);
	}

	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{
		DrawSnake(data.snake, window);
		DrawApple(data.apple, window);
		DrawUI(data.ui, window);
		for (auto& fence : data.fence)
		{
			DrawFence(*fence, window);
		}
	}
}