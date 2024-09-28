#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "GameSettings.h"

namespace SnakeGame
{
	struct Game;

	struct GameStateDifficultyData
	{
		sf::Font font;

		MenuItem beginnerItem;
		MenuItem easyItem;
		MenuItem normalItem;
		MenuItem hardItem;
		MenuItem challengingItem;
		MenuItem backItem;
		Menu menu;

		sf::Texture markTexture;
		sf::RectangleShape markShape;
	};

	void InitGameStateDifficulty(GameStateDifficultyData& data);
	void ShutdownGameStateDifficulty(GameStateDifficultyData& data);
	void HandleGameStateDifficultyWindowEvent(GameStateDifficultyData& data, Game& game, const sf::Event& event, const sf::Vector2i mousePosition);
	void UpdateGameStateDifficulty(GameStateDifficultyData& data, Game& game);
	void DrawGameStateDifficulty(GameStateDifficultyData& data, Game& game, sf::RenderWindow& window);
	void RunSelectedItem(GameStateDifficultyData& data, Game& game);
}
