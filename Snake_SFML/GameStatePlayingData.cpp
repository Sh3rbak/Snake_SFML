#include "GameStatePlayingData.h"
#include "Game.h"

namespace SnakeGame
{
	void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		ClearGameGrid(data.gameGrid);
		InitGameGrid(data.gameGrid);
		InitSnake(data.head);
		InitApple(data.apple);

		PositionInGrid positionCenterGrid = { GRID_CELLS_HORIZONTAL / 2, GRID_CELLS_VERTICAL / 2 };
		GridCell* centreGrid = &data.gameGrid.cells[positionCenterGrid.x][positionCenterGrid.y];
		SetSnakePosition(data.head, centreGrid->position, { positionCenterGrid.x, positionCenterGrid.y });
		AddItemToCell(data.gameGrid.cells[positionCenterGrid.x][positionCenterGrid.y], data.head);
	}
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PushGameState(game, GameStateType::ExitDialog, false);
			}
		}
	}
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float deltaTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			data.head.direction = SnakeDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			data.head.direction = SnakeDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			data.head.direction = SnakeDirection::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			data.head.direction = SnakeDirection::Left;
		}

		data.timeBetweenLoop += deltaTime;
		if(data.timeBetweenLoop < PAUSE_BETWEEN_LOOP)
		{
			return;
		}
		data.timeBetweenLoop = 0;


		PositionInGrid currectPositionInGrid = data.head.positionInGrid;
		GridCell* currectCell = &data.gameGrid.cells[currectPositionInGrid.x][currectPositionInGrid.y];
		RemoteItemFromCell(*currectCell, data.head);

		switch (data.head.direction)
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
		currectCell = &data.gameGrid.cells[currectPositionInGrid.x][currectPositionInGrid.y];
		SetSnakePosition(data.head, currectCell->position , { currectPositionInGrid.x, currectPositionInGrid.y });
		AddItemToCell(*currectCell, data.head);
				
	}
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{
		DrawSnake(data.head, window);
		DrawApple(data.apple, window);
	}
}