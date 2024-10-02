#include "GameStateGameOver.h"
#include "Game.h"
#include <cassert>

namespace SnakeGame
{
	void InitGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		assert(data.fontTitle.loadFromFile(RESOURCES_PATH + "Fonts/SerpensRegular.ttf"));
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Retro-Gaming.ttf"));

		if (game.isWinGame)
		{
			SetTextParametrs(data.menu.rootItem.hintText, "YOU WIN", data.fontTitle, CHARACTER_SIZE_CUSTOM_TITLE, sf::Color::Green);
		}
		else
		{
			SetTextParametrs(data.menu.rootItem.hintText, "GAME OVER", data.fontTitle, CHARACTER_SIZE_CUSTOM_TITLE, sf::Color::Red);
		}

		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 30.f;
		data.menu.rootItem.children.push_back(&data.goToMenuItem);
		data.menu.rootItem.children.push_back(&data.newGameItem);

		SetTextParametrs(data.goToMenuItem.text, "Menu", data.font, CHARACTER_SIZE_INIT_MENU);
		SetTextParametrs(data.newGameItem.text, "New Game", data.font, CHARACTER_SIZE_INIT_MENU);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.newGameItem);

		SetTextParametrs(data.finalScoreText, "Score:", data.font, CHARACTER_SIZE_INIT_MENU);
		data.finalScoreText.setString("Score:  " + std::to_string(game.gameScore));

		SetTextParametrs(data.recordsTableText, "Records:", data.font, CHARACTER_SIZE_INIT_MENU);

		PlayGameSounds(game.sound, static_cast<uint8_t>(game.options), SoundOption::Lose);
	}

	void ShutdownGameStateGameOver(GameStateGameOverData& data)
	{
		// No need to do anything here
	}

	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event, const sf::Vector2i mousePosition)
	{
		if (!data.menu.selectedItem)
		{
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Enter)
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

	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		if (data.isRunGameStateEnterNameData)
		{
			if (game.recordsTable.empty())
			{
				PushGameState(game, GameStateType::EnterName, true);
				data.isRunGameStateEnterNameData = false;
			}

			for (auto& record : game.recordsTable)
			{
				if (game.gameScore > record.second)
				{
					PushGameState(game, GameStateType::EnterName, true);
					data.isRunGameStateEnterNameData = false;
				}
			}
		}

		if (game.recordsTable.empty())
		{
			data.recordsTableText.setString("Records: Empty");
			return;
		}

		std::vector<std::pair<std::string, int>> recordTable;
		for (const auto& it : game.recordsTable)
		{
			recordTable.push_back({it.first, it.second});
		}
		auto cmp = [](std::pair<std::string, int>& left, std::pair<std::string, int>& right)
		{
				return left.second > right.second;
		};
		std::sort(recordTable.begin(), recordTable.end(), cmp);
		
		data.recordsTableText.setString("Records:");
		for (int i = 0; i < game.recordsTable.size() && i < RECORDS_TABLE_SIZE_IN_GAME_OVER; ++i)
		{
			std::string name = recordTable[i].first;
			std::string score = std::to_string(recordTable[i].second);
			data.recordsTableText.setString(data.recordsTableText.getString() + "\n" + name + ":  " + score);
		}
	}

	void DrawGameStateGameOver(GameStateGameOverData& data, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 50.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, {viewSize.x / 2.f, viewSize.y * (4.f / 5.f)}, {0.5f, 0.f});

		data.finalScoreText.setOrigin(GetItemOrigin(data.finalScoreText, { 0.5f, 0.5f }));
		data.finalScoreText.setPosition(viewSize.x / 4.f, viewSize.y * 3.f / 5.f);
		window.draw(data.finalScoreText);

		data.recordsTableText.setOrigin(GetItemOrigin(data.recordsTableText, { 0.5f, 0.5f }));
		data.recordsTableText.setPosition(viewSize.x / 4.f * 3.f, viewSize.y * 3.f / 5.f);
		window.draw(data.recordsTableText);
	}

	void RunSelectedItem(GameStateGameOverData& data, Game& game)
	{
		PlayGameSounds(game.sound, static_cast<uint8_t>(game.options), SoundOption::Enter);
		if (data.menu.selectedItem == &data.newGameItem)
		{
			SwitchGameState(game, GameStateType::Playing);
		}
		else if (data.menu.selectedItem == &data.goToMenuItem)
		{
			SwitchGameState(game, GameStateType::MainMenu);
		}
	}
}
