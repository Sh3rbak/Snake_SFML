#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "InputFields.h"
#include <unordered_map>

namespace SnakeGame
{
	struct Game;

	struct GameStateEnterNameData
	{
		sf::Font font;

		MenuItem yesItme;
		MenuItem noItem;
		MenuItem enterItem;
		Menu menu;

		InputFields inputFields;

		std::vector<char> inputLetters;
		std::string newName = "";
		sf::Text newNameText;
		bool isClearedDefaultName = false;

		std::vector<std::pair<std::string, int>> newRecordsTable;
	};

	void InitGameStateEnterName(GameStateEnterNameData& data, Game& game);
	void ShutdownGameStateEnterName(GameStateEnterNameData& data, Game& game);
	void HandleGameStateEnterNameWindowEvent(GameStateEnterNameData& data, Game& game, const sf::Event& event, const sf::Vector2i mousePosition);
	void UpdateGameStateEnterName(GameStateEnterNameData& data, Game& game);
	void DrawGameStateEnterName(GameStateEnterNameData& data, Game& game, sf::RenderWindow& window);
	void RunSelectedItem(GameStateEnterNameData& data, Game& game);
}
