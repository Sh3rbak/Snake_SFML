#include "GameStateDifficulty.h"
#include "Game.h"
#include <cassert>

namespace SnakeGame
{
	void InitGameStateDifficulty(GameStateDifficultyData& data)
	{
		assert(data.markTexture.loadFromFile(RESOURCES_PATH + "Textures/check-mark.png"));
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Retro-Gaming.ttf"));

		data.markShape.setSize({ 40.f, 40.f });
		data.markShape.setOrigin({ data.markShape.getSize().x / 2.f, 0.f });
		data.markShape.setTexture(&data.markTexture);

		SetTextParametrs(data.menu.rootItem.hintText, "Difficulty", data.font, CHARACTER_SIZE_DEFAULT_TITLE);
		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 20.f;
		data.menu.rootItem.children.push_back(&data.beginnerItem);
		data.menu.rootItem.children.push_back(&data.easyItem);
		data.menu.rootItem.children.push_back(&data.normalItem);
		data.menu.rootItem.children.push_back(&data.hardItem);
		data.menu.rootItem.children.push_back(&data.challengingItem);
		data.menu.rootItem.children.push_back(&data.backItem);

		SetTextParametrs(data.beginnerItem.text, "Beginner", data.font, CHARACTER_SIZE_INIT_MENU);
		SetTextParametrs(data.easyItem.text, "Easy", data.font, CHARACTER_SIZE_INIT_MENU);
		SetTextParametrs(data.normalItem.text, "Normal", data.font, CHARACTER_SIZE_INIT_MENU);
		SetTextParametrs(data.hardItem.text, "Hard", data.font, CHARACTER_SIZE_INIT_MENU);
		SetTextParametrs(data.challengingItem.text, "Challenging", data.font, CHARACTER_SIZE_INIT_MENU);
		SetTextParametrs(data.backItem.text, "Back", data.font, CHARACTER_SIZE_INIT_MENU);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.normalItem);
	}

	void ShutdownGameStateDifficulty(GameStateDifficultyData& data)
	{
		// No need to do anything here
	}

	void HandleGameStateDifficultyWindowEvent(GameStateDifficultyData& data, Game& game, const sf::Event& event, const sf::Vector2i mousePosition)
	{
		if (!data.menu.selectedItem)
		{
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::B)
			{
				PopGameState(game);
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

	void UpdateGameStateDifficulty(GameStateDifficultyData& data, Game& game)
	{
		// No need to do anything here
	}

	void DrawGameStateDifficulty(GameStateDifficultyData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });

		switch (game.difficulty)
		{
		case SnakeGame::GameDifficulty::Beginner:
			data.markShape.setPosition({viewSize.x * 2.f / 3.f, data.beginnerItem.text.getPosition().y });
			break;
		case SnakeGame::GameDifficulty::Easy:
			data.markShape.setPosition({ viewSize.x * 2.f / 3.f, data.easyItem.text.getPosition().y });
			break;
		case SnakeGame::GameDifficulty::Normal:
			data.markShape.setPosition({ viewSize.x * 2.f / 3.f, data.normalItem.text.getPosition().y });
			break;
		case SnakeGame::GameDifficulty::Hard:
			data.markShape.setPosition({ viewSize.x * 2.f / 3.f, data.hardItem.text.getPosition().y });
			break;
		case SnakeGame::GameDifficulty::Challenge:
			data.markShape.setPosition({ viewSize.x * 2.f / 3.f, data.challengingItem.text.getPosition().y });
			break;
		}

		window.draw(data.markShape);
	}

	void RunSelectedItem(GameStateDifficultyData& data, Game& game)
	{
		PlayGameSounds(game.sound, static_cast<uint8_t>(game.options), SoundOption::Enter);
		if (data.menu.selectedItem == &data.beginnerItem)
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
		else if (data.menu.selectedItem == &data.backItem)
		{
			PopGameState(game);
		}
	}
}