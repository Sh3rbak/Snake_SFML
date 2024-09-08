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
		data.menu.rootItem.children.push_back(&data.gameModsItem);
		data.menu.rootItem.children.push_back(&data.settingsItem);
		data.menu.rootItem.children.push_back(&data.leaderBoardItem);
		data.menu.rootItem.children.push_back(&data.exitGameItem);

		setTextParametrs(data.startGameItem.text, "Start Game", data.font, 36);

		setTextParametrs(data.gameModsItem.text, "Game Mods", data.font, 36);


		setTextParametrs(data.settingsItem.text, "Setting", data.font, 36);

		
		setTextParametrs(data.leaderBoardItem.text, "Leader Board", data.font, 36);

		setTextParametrs(data.exitGameItem.text, "Exit", data.font, 36);
		setTextParametrs(data.exitGameItem.hintText, "Are you sure you want to exist?", data.font, 48, sf::Color::White);
		data.exitGameItem.childrenOrientation = Orientation::Vertical;
		data.exitGameItem.childrenAlignment = Alignment::Middle;
		data.exitGameItem.childrenSpacing = 20.f;
		data.exitGameItem.children.push_back(&data.yesItem);
		data.exitGameItem.children.push_back(&data.noItem);

		setTextParametrs(data.yesItem.text, "Yes", data.font, 36);
		setTextParametrs(data.noItem.text, "No", data.font, 36);

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
			if (event.key.code == sf::Keyboard::Escape)
			{
				CollapseSelectedItem(data.menu);
			} 
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (data.menu.selectedItem == &data.startGameItem)
				{
					SwitchGameState(game, GameStateType::Playing);
				}
				else if (data.menu.selectedItem == &data.exitGameItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.yesItem)
				{
					SwitchGameState(game, GameStateType::None);
				}
				else if (data.menu.selectedItem == &data.noItem)
				{
					CollapseSelectedItem(data.menu);
				}
			}

			Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				SelectPreviousMenuItem(data.menu);
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
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
