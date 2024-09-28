#include "GameStateMainMenu.h"
#include "Game.h"
#include <cassert>

namespace SnakeGame
{
	void InitGameStateMainMenu(GameStateMainMenuData& data)
	{
		assert(data.fontTitle.loadFromFile(RESOURCES_PATH + "Fonts/SerpensRegular.ttf"));
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Retro-Gaming.ttf"));

		SetTextParametrs(data.menu.rootItem.hintText, "SNAKE", data.fontTitle, CHARACTER_SIZE_CUSTOM_TITLE, sf::Color::Green);
		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 20.f;
		data.menu.rootItem.children.push_back(&data.startGameItem);
		data.menu.rootItem.children.push_back(&data.gameDifficultyItem);
		data.menu.rootItem.children.push_back(&data.leaderBoardItem);
		data.menu.rootItem.children.push_back(&data.optionsItem);
		data.menu.rootItem.children.push_back(&data.exitGameItem);

		SetTextParametrs(data.startGameItem.text, "Start Game", data.font, CHARACTER_SIZE_INIT_MENU);
		SetTextParametrs(data.gameDifficultyItem.text, "Difficulty", data.font, CHARACTER_SIZE_INIT_MENU);
		SetTextParametrs(data.leaderBoardItem.text, "Leader Board", data.font, CHARACTER_SIZE_INIT_MENU);
		SetTextParametrs(data.optionsItem.text, "Options", data.font, CHARACTER_SIZE_INIT_MENU);

		SetTextParametrs(data.exitGameItem.text, "Exit", data.font, CHARACTER_SIZE_INIT_MENU);
		SetTextParametrs(data.exitGameItem.hintText, "Are you sure you want to exist?", data.font, CHARACTER_SIZE_DEFAULT_TITLE, sf::Color::White);
		data.exitGameItem.childrenOrientation = Orientation::Vertical;
		data.exitGameItem.childrenAlignment = Alignment::Middle;
		data.exitGameItem.childrenSpacing = 20.f;
		data.exitGameItem.children.push_back(&data.noItem);
		data.exitGameItem.children.push_back(&data.yesItem);

		SetTextParametrs(data.noItem.text, "No", data.font, CHARACTER_SIZE_INIT_MENU);
		SetTextParametrs(data.yesItem.text, "Yes", data.font, CHARACTER_SIZE_INIT_MENU);


		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.startGameItem);
	}

	void ShutdownGameStateMainMenu(GameStateMainMenuData& data)
	{
		// No need to do anything here
	}

	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event, const sf::Vector2i mousePosition)
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
				PlayGameSounds(game.sound, static_cast<uint8_t>(game.options), SoundOption::Enter);
			} 
			else if (event.key.code == sf::Keyboard::Enter)
			{
				RunSelectedItem(data, game);
			}

			Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left ||
				event.key.code == sf::Keyboard::W)
			{
				SelectPreviousMenuItem(data.menu);
				PlayGameSounds(game.sound, static_cast<uint8_t>(game.options), SoundOption::Hover);
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right ||
				event.key.code == sf::Keyboard::S)
			{
				SelectNextMenuItem(data.menu);
				PlayGameSounds(game.sound, static_cast<uint8_t>(game.options), SoundOption::Hover);
			}
		}
		
		MenuItem* expandedItem = GetCurrentMenuContext(data.menu);
		for (auto& child : expandedItem->children)
		{
			if (IsMouseOnItem(mousePosition, child->text))
			{
				if (data.menu.selectedItem != child)
				{
					SelectMenuItem(data.menu, child);
					PlayGameSounds(game.sound, static_cast<uint8_t>(game.options), SoundOption::Hover);
				}
				if (event.type == sf::Event::MouseButtonReleased)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						RunSelectedItem(data, game);
					}
				}
			}
		}
	}

	void UpdateGameStateMainMenu(GameStateMainMenuData& data)
	{
		// No need to do anything here
	}

	void DrawGameStateMainMenu(GameStateMainMenuData& data, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });
	}

	void RunSelectedItem(GameStateMainMenuData& data, Game& game)
	{
		PlayGameSounds(game.sound, static_cast<uint8_t>(game.options), SoundOption::Enter);
		if (data.menu.selectedItem == &data.startGameItem)
		{
			SwitchGameState(game, GameStateType::Playing);
		}
		else if (data.menu.selectedItem == &data.gameDifficultyItem)
		{
			PushGameState(game, GameStateType::Difficulty, true);
		}
		else if (data.menu.selectedItem == &data.leaderBoardItem)
		{
			PushGameState(game, GameStateType::LeaderBoard, true);
		}
		else if (data.menu.selectedItem == &data.optionsItem)
		{
			PushGameState(game, GameStateType::Options, true);
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
}
