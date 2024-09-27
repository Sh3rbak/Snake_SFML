#include "GameStateLeaderBoard.h"
#include "Game.h"
#include <cassert>

namespace SnakeGame
{
	void InitGameStateLeaderBoard(GameStateLeaderBoardData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Retro-Gaming.ttf"));

		SetTextParametrs(data.menu.rootItem.hintText, "Leader Board", data.font, CHARACTER_SIZE_DEFAULT_TITLE, sf::Color::White);
		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.children.push_back(&data.backItem);

		SetTextParametrs(data.backItem.text, "Back", data.font, CHARACTER_SIZE_INIT_MENU);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.backItem);

		std::vector<std::pair<std::string, int>> recordTable;
		for (const auto& it : game.recordsTable)
		{
			recordTable.push_back({ it.first, it.second });
		}
		auto cmp = [](std::pair<std::string, int>& left, std::pair<std::string, int>& right)
			{
				return left.second > right.second;
			};
		std::sort(recordTable.begin(), recordTable.end(), cmp);

		SetTextParametrs(data.leaderNumberText, "", data.font, CHARACTER_SIZE_INIT_MENU, sf::Color::White);
		SetTextParametrs(data.leaderNamesText, "", data.font, CHARACTER_SIZE_INIT_MENU, sf::Color::White);
		SetTextParametrs(data.leaderScoresText, "", data.font, CHARACTER_SIZE_INIT_MENU, sf::Color::White);

		for (int i = 0; i < game.recordsTable.size() && i < RECORDS_TABLE_SIZE_IN_GAME_OVER; ++i)
		{
			std::string number = std::to_string(i + 1);
			std::string name = recordTable[i].first;
			std::string score = std::to_string(recordTable[i].second);
			
			data.leaderNumberText.setString(data.leaderNumberText.getString() + "\n" + number);
			data.leaderNamesText.setString(data.leaderNamesText.getString() + "\n" + name);
			data.leaderScoresText.setString(data.leaderScoresText.getString() + "\n" + score);
		}
	}

	void ShutdownGameStateLeaderBoard(GameStateLeaderBoardData& data)
	{
		// No need to do anything here
	}

	void HandleGameStateLeaderBoardWindowEvent(GameStateLeaderBoardData& data, Game& game, const sf::Event& event, sf::Vector2i mousePosition)
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
				PlayEnterSoundMenu(data.menu);
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
				PlayHoverSoundMenu(data.menu);
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right ||
				event.key.code == sf::Keyboard::S)
			{
				SelectNextMenuItem(data.menu);
				PlayHoverSoundMenu(data.menu);
			}
		}

		MenuItem* expandedItem = GetCurrentMenuContext(data.menu);
		for (auto& child : expandedItem->children)
		{
			if (IsMouseOnText(mousePosition, child->text))
			{
				if (data.menu.selectedItem != child)
				{
					SelectMenuItem(data.menu, child);
					PlayHoverSoundMenu(data.menu);
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

	void UpdateGameStateLeaderBoard(GameStateLeaderBoardData& data, Game& game)
	{
		// No need to do anything here
	}

	void DrawGameStateLeaderBoard(GameStateLeaderBoardData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 100.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, { viewSize.x / 2.f, viewSize.y * (4.f / 5.f) }, { 0.5f, 0.f });

		data.leaderNumberText.setOrigin(GetItemOrigin(data.leaderNumberText, { 0.5f, 0.5f }));
		data.leaderNumberText.setPosition(viewSize.x / 2.f - 100.f, viewSize.y / 2.f);

		data.leaderNamesText.setOrigin(GetItemOrigin(data.leaderNamesText, { 0.5f, 0.5f }));
		data.leaderNamesText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f);

		data.leaderScoresText.setOrigin(GetItemOrigin(data.leaderScoresText, { 0.5f, 0.5f }));
		data.leaderScoresText.setPosition(viewSize.x / 2.f + 100.f, viewSize.y / 2.f);

		window.draw(data.leaderNumberText);
		window.draw(data.leaderNamesText);
		window.draw(data.leaderScoresText);
	}

	void RunSelectedItem(GameStateLeaderBoardData& data, Game& game)
	{
		PlayEnterSoundMenu(data.menu);
		if (data.menu.selectedItem == &data.backItem)
		{
			PopGameState(game);
		}
	}
}

