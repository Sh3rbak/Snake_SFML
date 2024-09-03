#include "GameStatePlaying.h"
#include <cassert>
#include "Game.h"

namespace SnakeGame
{
	void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		assert(data.headSnakeTexture.loadFromFile(RESOURCES_PATH + "Textures/SnakeHead.png"));
		assert(data.bodySnakeTexture.loadFromFile(RESOURCES_PATH + "Textures/SnakeBody.png"));

		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Retro-Gaming.ttf"));
		InitUI(data.ui, data.font);

		InitGameGrid(data.gameGrid);
		InitSnakeHead(data.snake, data.headSnakeTexture);
		InitApple(data.apple);

		data.numEatenApples = 0;

		PositionInGrid positionCenterGrid = { GRID_CELLS_HORIZONTAL / 2, GRID_CELLS_VERTICAL / 2 };
		GridCell* centerGrid = &data.gameGrid.cells[positionCenterGrid.x][positionCenterGrid.y];
		SetSnakeHeadPosition(data.snake, centerGrid->position, { positionCenterGrid.x, positionCenterGrid.y });
		ChangeTypeCell(*centerGrid, GameItemType::Snake);

		GridCell* randomCell = GetRandomCell(data.gameGrid);
		SetApplePosition(data.apple, randomCell->position);
		ChangeTypeCell(*randomCell, GameItemType::Apple);
	}

	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		ClearGameGrid(data.gameGrid);
		ClearSnake(data.snake);
	}

	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event event, sf::Vector2i mousePosition)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PushGameState(game, GameStateType::ExitDialog, false);
			}
		}
		sf::FloatRect pauseRect = GetGlobalBoundsOfPauseButton(data.ui);
		if (mousePosition.x > pauseRect.left && mousePosition.x < pauseRect.left + pauseRect.width &&
			mousePosition.y > pauseRect.top && mousePosition.y < pauseRect.top + pauseRect.height)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				SwitchGameState(game, GameStateType::Playing);
			}
		}
	}

	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float deltaTime)
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

		switch (GetSnakeHeadDirection(data.snake))
		{
		case SnakeDirection::Left:
		{
			--currectPositionInGrid.x;
			break;
		}
		case SnakeDirection::Up:
		{
			--currectPositionInGrid.y;
			break;
		}
		case SnakeDirection::Right:
		{
			++currectPositionInGrid.x;
			break;
		}
		case SnakeDirection::Down:
		{
			++currectPositionInGrid.y;
			break;
		}
		}

		//checking collision with board
		if (currectPositionInGrid.x < 0 || currectPositionInGrid.x >= GRID_CELLS_HORIZONTAL ||
			currectPositionInGrid.y < 0 || currectPositionInGrid.y >= GRID_CELLS_VERTICAL)
		{
			SwitchGameState(game, GameStateType::Playing);
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
					randomCell = GetRandomCell(data.gameGrid);
					++score;
					if (score > 10)
					{
						randomCell = FindEmptyCell(data.gameGrid);
					}
				}
				//if run out of free cells
				if (randomCell == nullptr)
				{
					SwitchGameState(game, GameStateType::Playing);
				}
				SetApplePosition(data.apple, randomCell->position);
				ChangeTypeCell(*randomCell, GameItemType::Apple);
				PushPartOfBody(data.snake, data.bodySnakeTexture);
				++data.numEatenApples;
				break;
			}
			case SnakeGame::GameItemType::Snake:
			{
				SwitchGameState(game, GameStateType::Playing);
				break;
			}
			}
		}

		//clearing type of cells
		std::vector<PositionInGrid> positionSnakeInGrid = GetPositionSnake(data.snake);
		for (auto it = positionSnakeInGrid.begin(); it != positionSnakeInGrid.end(); ++it)
		{
			ClearTypeCell(data.gameGrid.cells[it->x][it->y]);
		}

		UpdateSnakeBody(data.snake);
		SetSnakeHeadPosition(data.snake, currectCell->position , { currectPositionInGrid.x, currectPositionInGrid.y });
		
		//filling in type of cells with Snake
		positionSnakeInGrid = GetPositionSnake(data.snake);
		for (auto it = positionSnakeInGrid.begin(); it != positionSnakeInGrid.end(); ++it)
		{
			ChangeTypeCell(data.gameGrid.cells[it->x][it->y], GameItemType::Snake);
		}	
		UpdateUI(data.ui, data.numEatenApples);
	}

	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{
		DrawSnake(data.snake, window);
		DrawApple(data.apple, window);
		DrawUI(data.ui, window);
	}
}