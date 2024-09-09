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
		data.menu.rootItem.childrenSpacing = 20.f;
		data.menu.rootItem.children.push_back(&data.newGameItem);
		data.menu.rootItem.children.push_back(&data.goToMenuItem);

		setTextParametrs(data.newGameItem.text, "New Game", data.font, 36);
		setTextParametrs(data.goToMenuItem.text, "Go to Menu", data.font, 36);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.newGameItem);
	}
	void ShutdownGameStateGameOver(GameStateGameOverData& data)
	{
	}
	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event)
	{
		if (!data.menu.selectedItem)
		{
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Enter)
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
	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
	}
	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });
	}
}
