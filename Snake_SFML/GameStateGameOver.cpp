#include "GameStateGameOver.h"
#include "Game.h"
#include <cassert>

namespace SnakeGame
{
	void InitGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		assert(data.fontTitle.loadFromFile(RESOURCES_PATH + "Fonts/SerpensRegular.ttf"));
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Retro-Gaming.ttf"));

		auto setTextParametrs = [](sf::Text& text, const std::string title, sf::Font& font, int size,
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
		
		if (game.isWinGame)
		{
			setTextParametrs(data.menu.rootItem.hintText, "YOU WIN", data.fontTitle, 200, sf::Color::Green);
		}
		else
		{
			setTextParametrs(data.menu.rootItem.hintText, "GAME OVER", data.fontTitle, 200, sf::Color::Red);
		}

		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 30.f;
		data.menu.rootItem.children.push_back(&data.newGameItem);
		data.menu.rootItem.children.push_back(&data.goToMenuItem);

		setTextParametrs(data.newGameItem.text, "New Game", data.font, 36);
		setTextParametrs(data.goToMenuItem.text, "Go to Menu", data.font, 36);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.newGameItem);

		setTextParametrs(data.finalScoreText, "Score:", data.font, 28);
		setTextParametrs(data.recordsTableText, "Leaders:", data.font, 28);
	}

	void ShutdownGameStateGameOver(GameStateGameOverData& data)
	{
		// No need to do anything here
	}

	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event, sf::Vector2i mousePosition)
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
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right ||
				event.key.code == sf::Keyboard::S)
			{
				SelectNextMenuItem(data.menu);
			}
		}
		MenuItem* expandedItem = GetCurrentMenuContext(data.menu);
		for (auto& child : expandedItem->children)
		{
			if (IsMouseOnText(mousePosition, child->text))
			{
				SelectMenuItem(data.menu, child);
				if (event.key.code == sf::Mouse::Left)
				{
					RunSelectedItem(data, game);
				}
			}
		}
	}

	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		data.finalScoreText.setString("Score:  " + std::to_string(game.gameScore));

		if (game.recordsTable.empty())
		{
			data.recordsTableText.setString("Records: Empty");
			return;
		}
		data.recordsTableText.setString("Records:");
		int score = 0;
		for (const auto& it : game.recordsTable)
		{
			data.recordsTableText.setString(data.recordsTableText.getString() + "\n" + it.first + ":  " + std::to_string(it.second));
			++score;
			if (score >= 3)
			{
				break;
			}
		}
	}

	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 50.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, {viewSize.x / 2.f, viewSize.y * (4.f / 5.f)}, {0.5f, 0.f});

		data.finalScoreText.setOrigin(GetItemOrigin(data.finalScoreText, { 0.5f, 0.5f }));
		data.finalScoreText.setPosition(viewSize.x / 4.f, viewSize.y / 2.f);
		window.draw(data.finalScoreText);

		data.recordsTableText.setOrigin(GetItemOrigin(data.recordsTableText, { 0.5f, 0.5f }));
		data.recordsTableText.setPosition(viewSize.x / 4.f * 3.f, viewSize.y / 2.f);
		window.draw(data.recordsTableText);
	}

	void RunSelectedItem(GameStateGameOverData& data, Game& game)
	{
		if (data.menu.selectedItem == &data.goToMenuItem)
		{
			SwitchGameState(game, GameStateType::MainMenu);
		}
		else if (data.menu.selectedItem == &data.newGameItem)
		{
			SwitchGameState(game, GameStateType::Playing);
		}
	}
}
