#include "GameStatePlaying.h"
#include <cassert>
#include "Game.h"

namespace SnakeGame
{
	void SetFence(GameStatePlayingData& data, sf::Texture& fenceTexture, sf::Texture& fenceInCornerTexture)
	{
		auto setFence = [&data](GridCell& cell, sf::Texture& texture, Direction direction,
			GameItemType type = GameItemType::Fence)
			{
				cell.type = type;
				data.fence.push_back(new Fence);
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
		assert(data.headSnakeTexture.loadFromFile(RESOURCES_PATH + "Textures/SnakeHead.png"));
		assert(data.bodySnakeTexture.loadFromFile(RESOURCES_PATH + "Textures/SnakeBody.png"));
		assert(data.appleTexture.loadFromFile(RESOURCES_PATH + "Textures/Apple.png"));

		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Retro-Gaming.ttf"));
		InitUI(data.ui, data.font);

		assert(data.fenceTexture.loadFromFile(RESOURCES_PATH + "Textures/fence.png", sf::IntRect(8, 0, 8, 8)));
		assert(data.fenceInCornerTexture.loadFromFile(RESOURCES_PATH + "Textures/fence.png", sf::IntRect(0, 0, 8, 8)));

		InitGameGrid(data.gameGrid);
		InitSnakeHead(data.snake, data.headSnakeTexture);
		InitApple(data.apple, data.appleTexture);

		data.numEatenApples = 0;

		int perimeter = (GRID_CELLS_VERTICAL * 2) + ((GRID_CELLS_HORIZONTAL - 2) * 2);
		data.fence.reserve(perimeter);
		SetFence(data, data.fenceTexture, data.fenceInCornerTexture);

		PositionInGrid positionCenterGrid = { GRID_CELLS_HORIZONTAL / 2, GRID_CELLS_VERTICAL / 2 };
		GridCell* centerGrid = &data.gameGrid.cells[positionCenterGrid.x][positionCenterGrid.y];
		SetSnakeHeadPosition(data.snake, centerGrid->position, { positionCenterGrid.x, positionCenterGrid.y });
		ChangeTypeCell(*centerGrid, GameItemType::Snake);

		GridCell* randomCell = GetRandomCell(data.gameGrid);
		SetApplePosition(data.apple, randomCell->position);
		ChangeTypeCell(*randomCell, GameItemType::Apple);
	}

	void ShutdownGameStatePlaying(GameStatePlayingData& data)
	{
		ClearGameGrid(data.gameGrid);
		ClearSnake(data.snake);
		for (auto it : data.fence)
		{
			delete it;
		}
	}

	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event event, sf::Vector2i mousePosition)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PushGameState(game, GameStateType::Pause, false);
			}
		}
		if (IsMouseOnText(mousePosition, data.ui.pauseText))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				PushGameState(game, GameStateType::Pause, false);
			}
		}
	}

	void SetNewDirection(GameStatePlayingData& data)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			data.newDirection = SnakeDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			data.newDirection = SnakeDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			data.newDirection = SnakeDirection::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
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
		SetNewDirection(data);

		// delay between movement
		data.timeBetweenLoop += deltaTime;
		if(data.timeBetweenLoop < PAUSE_BETWEEN_LOOP)
		{
			return;
		}
		data.timeBetweenLoop = 0;
		
		SetSnakeHeadDirection(data.snake, data.newDirection);

		//calculate the next cell
		PositionInGrid currectPositionInGrid = GetSnakeHeadPositionInGrid(data.snake);
		GridCell* currectCell = &data.gameGrid.cells[currectPositionInGrid.x][currectPositionInGrid.y];

		CalculateNextCellDependingOnDirection(data, currectPositionInGrid);

		//checking collision with board
		if (currectPositionInGrid.x < 0 || currectPositionInGrid.x >= GRID_CELLS_HORIZONTAL ||
			currectPositionInGrid.y < 0 || currectPositionInGrid.y >= GRID_CELLS_VERTICAL)
		{
			SwitchGameState(game, GameStateType::GameOver);
			return;
		}

		currectCell = &data.gameGrid.cells[currectPositionInGrid.x][currectPositionInGrid.y];

		if (IsAnythingInCell(*currectCell))
		{
			switch (currectCell->type)
			{
			case SnakeGame::GameItemType::Apple:
			{
				ClearTypeCell(*currectCell);
				auto randomCell = GetRandomCell(data.gameGrid);
				int score = 0;
				// find free cells
				while (IsAnythingInCell(*randomCell))
				{
					if (score > 10)
					{
						randomCell = FindEmptyCell(data.gameGrid);
					}
					randomCell = GetRandomCell(data.gameGrid);
					++score;
				}
				//if run out of free cells
				if (randomCell == nullptr)
				{
					SwitchGameState(game, GameStateType::GameOver);
				}
				SetApplePosition(data.apple, randomCell->position);
				ChangeTypeCell(*randomCell, GameItemType::Apple);
				PushPartOfBody(data.snake, data.bodySnakeTexture);
				++data.numEatenApples;
				break;
			}
			case SnakeGame::GameItemType::Snake:
			case SnakeGame::GameItemType::Fence:
			{
				SwitchGameState(game, GameStateType::GameOver);
				break;
			}
			}
		}

		UpdateCellsTypeWhenSnakeMoves(data, *currectCell, currectPositionInGrid);

		UpdateUI(data.ui, data.numEatenApples);
	}

	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{
		DrawSnake(data.snake, window);
		DrawApple(data.apple, window);
		DrawUI(data.ui, window);
		for (auto fence : data.fence)
		{
			DrawFence(*fence, window);
		}
	}
}