#include "GameStatePause.h"
#include "Game.h"
#include <cassert>

namespace SnakeGame
{
	void InitGameStatePause(GameStatePauseData& data, Game& game)
	{
		assert(data.fontTitle.loadFromFile(RESOURCES_PATH + "Fonts/SerpensRegular.ttf"));
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Retro-Gaming.ttf"));

		SetTextParametrs(data.menu.rootItem.hintText, "PAUSE", data.fontTitle, 200, sf::Color::Red);
		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 20.f;
		data.menu.rootItem.children.push_back(&data.continueItem);
		data.menu.rootItem.children.push_back(&data.newGameItem);
		data.menu.rootItem.children.push_back(&data.goToMenuItem);

		SetTextParametrs(data.continueItem.text, "Continue", data.font, 36);
		SetTextParametrs(data.newGameItem.text, "New Game", data.font, 36);
		SetTextParametrs(data.goToMenuItem.text, "Go to Menu", data.font, 36);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.continueItem);

		data.backround.setSize({ SCREEN_WIDHT, SCREEN_HEIGHT });
		data.backround.setFillColor(sf::Color(0, 0, 0, 125));
	}

	void ShutdownGameStatePause(GameStatePauseData& data)
	{
		// No need to do anything here
	}
	void HandleGameStatePauseWindowEvent(GameStatePauseData& data, Game& game, const sf::Event& event, sf::Vector2i mousePosition)
	{
		if (!data.menu.selectedItem)
		{
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PopGameState(game);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				RunSelectedItem(data, game);
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

	void UpdateGameStatePause(GameStatePauseData& data, Game& game)
	{

	}

	void DrawGameStatePause(GameStatePauseData& data, Game& game, sf::RenderWindow& window)
	{
		window.draw(data.backround);

		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });
	}

	void RunSelectedItem(GameStatePauseData& data, Game& game)
	{
		if (data.menu.selectedItem == &data.continueItem)
		{
			PopGameState(game);
		}
		else if (data.menu.selectedItem == &data.newGameItem)
		{
			SwitchGameState(game, GameStateType::Playing);
		}
		else if (data.menu.selectedItem == &data.goToMenuItem)
		{
			SwitchGameState(game, GameStateType::MainMenu);
		}
	}
}
