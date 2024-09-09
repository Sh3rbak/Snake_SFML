#include "GameStateMainMenu.h"
#include "Game.h"
#include <cassert>

namespace SnakeGame
{
	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
		assert(data.fontTitle.loadFromFile(RESOURCES_PATH + "Fonts/SerpensRegular.ttf"));
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Retro-Gaming.ttf"));

		auto setTextParametrs = [](sf::Text& text, const std::string title, sf::Font& font, const int size,
			sf::Color color = sf::Color::Transparent)
			{
				text.setString(title);
				text.setFont(font);
				text.setCharacterSize(size);
				if (color != sf::Color::Transparent)
				{
					text.setFillColor(color);
				}
			};

		setTextParametrs(data.menu.rootItem.hintText, "SNAKE", data.fontTitle, 200, sf::Color::Green);
		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 10.f;
		data.menu.rootItem.children.push_back(&data.startGameItem);
		data.menu.rootItem.children.push_back(&data.gameDifficultyItem);
		data.menu.rootItem.children.push_back(&data.optionsItem);
		data.menu.rootItem.children.push_back(&data.leaderBoardItem);
		data.menu.rootItem.children.push_back(&data.exitGameItem);

		setTextParametrs(data.startGameItem.text, "Start Game", data.font, 36);

		setTextParametrs(data.gameDifficultyItem.text, "Difficulty", data.font, 36);
		setTextParametrs(data.gameDifficultyItem.hintText, "Difficulty", data.font, 48);
		data.gameDifficultyItem.childrenOrientation = Orientation::Vertical;
		data.gameDifficultyItem.childrenAlignment = Alignment::Middle;
		data.gameDifficultyItem.childrenSpacing = 20.f;
		data.gameDifficultyItem.children.push_back(&data.beginnerItem);
		data.gameDifficultyItem.children.push_back(&data.easyItem);
		data.gameDifficultyItem.children.push_back(&data.normalItem);
		data.gameDifficultyItem.children.push_back(&data.hardItem);
		data.gameDifficultyItem.children.push_back(&data.challengingItem);

		setTextParametrs(data.beginnerItem.text, "Beginner", data.font, 36);
		setTextParametrs(data.easyItem.text, "Easy", data.font, 36);
		setTextParametrs(data.normalItem.text, "Normal", data.font, 36);
		setTextParametrs(data.hardItem.text, "Hard", data.font, 36);
		setTextParametrs(data.challengingItem.text, "Challenging", data.font, 36);


		setTextParametrs(data.optionsItem.text, "Options", data.font, 36);

		
		setTextParametrs(data.leaderBoardItem.text, "Leader Board", data.font, 36);

		setTextParametrs(data.exitGameItem.text, "Exit", data.font, 36);
		setTextParametrs(data.exitGameItem.hintText, "Are you sure you want to exist?", data.font, 48, sf::Color::White);
		data.exitGameItem.childrenOrientation = Orientation::Vertical;
		data.exitGameItem.childrenAlignment = Alignment::Middle;
		data.exitGameItem.childrenSpacing = 20.f;
		data.exitGameItem.children.push_back(&data.noItem);
		data.exitGameItem.children.push_back(&data.yesItem);

		setTextParametrs(data.noItem.text, "No", data.font, 36);
		setTextParametrs(data.yesItem.text, "Yes", data.font, 36);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.startGameItem);
	}
	void ShutdownGameStateMainMenu(GameStateMainMenuData& data)
	{
	}
	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event)
	{
		if (!data.menu.selectedItem)
		{
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::B)
			{
				CollapseSelectedItem(data.menu);
			} 
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (data.menu.selectedItem == &data.startGameItem)
				{
					SwitchGameState(game, GameStateType::Playing);
				}
				else if (data.menu.selectedItem == &data.gameDifficultyItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.beginnerItem)
				{
					game.difficulty = GameDifficulty::Beginner;
				}
				else if (data.menu.selectedItem == &data.easyItem)
				{
					game.difficulty = GameDifficulty::Easy;
				}
				else if (data.menu.selectedItem == &data.normalItem)
				{
					game.difficulty = GameDifficulty::Normal;
				}
				else if (data.menu.selectedItem == &data.hardItem)
				{
					game.difficulty = GameDifficulty::Hard;
				}
				else if (data.menu.selectedItem == &data.challengingItem)
				{
					game.difficulty = GameDifficulty::Challenge;
				}
				else if (data.menu.selectedItem == &data.exitGameItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.noItem)
				{
					CollapseSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.yesItem)
				{
					SwitchGameState(game, GameStateType::None);
				}
			}

			Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left ||
				event.key.code == sf::Keyboard::W)
			{
				SelectPreviousMenuItem(data.menu);
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right ||
				event.key.code == sf::Keyboard::S)
			{
				SelectNextMenuItem(data.menu);
			}
		}
	}
	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
	}
	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });
	}
}
