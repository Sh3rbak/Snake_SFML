#include "GameStateOptions.h"
#include "Game.h"
#include <cassert>

namespace SnakeGame
{
	void InitGameStateOptions(GameStateOptionsData& data)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Retro-Gaming.ttf"));
		assert(data.checkMarkTexture.loadFromFile(RESOURCES_PATH + "Textures/check-mark.png"));
		assert(data.crossMarkTexture.loadFromFile(RESOURCES_PATH + "Textures/cross-mark.png"));

		SetTextParametrs(data.menu.rootItem.hintText, "Options", data.font, CHARACTER_SIZE_DEFAULT_TITLE, sf::Color::White);
		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 30.f;
		data.menu.rootItem.children.push_back(&data.soundItem);
		data.menu.rootItem.children.push_back(&data.musicItem);
		data.menu.rootItem.children.push_back(&data.backItem);

		SetTextParametrs(data.soundItem.text, "Sound", data.font, CHARACTER_SIZE_INIT_MENU);
		SetTextParametrs(data.musicItem.text, "Music", data.font, CHARACTER_SIZE_INIT_MENU);
		SetTextParametrs(data.backItem.text, "Back", data.font, CHARACTER_SIZE_INIT_MENU);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.soundItem);

		data.fieldMarkSoundShape.setSize({ 40.f, 40.f });
		data.fieldMarkSoundShape.setOutlineThickness(4.f);
		data.fieldMarkSoundShape.setOrigin({ data.fieldMarkSoundShape.getSize().x / 2.f, 0.f });

		data.fieldMarkMusicShape.setSize({ 40.f, 40.f });
		data.fieldMarkMusicShape.setOutlineThickness(4.f);
		data.fieldMarkMusicShape.setOrigin({ data.fieldMarkMusicShape.getSize().x / 2.f, 0.f });
	}

	void ShutdownGameStateOptions(GameStateOptionsData& data)
	{
		// No need to do anything here
	}

	void HandleGameStateOptionsWindowEvent(GameStateOptionsData& data, Game& game, const sf::Event& event, const sf::Vector2i mousePosition)
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
				RunSelectedItemByMouse(data, game, event, *child);
			}
		}
		if (IsMouseOnItem(mousePosition, data.fieldMarkSoundShape))
		{
			RunSelectedItemByMouse(data, game, event, data.soundItem);
		} 
		else if (IsMouseOnItem(mousePosition, data.fieldMarkMusicShape))
		{
			RunSelectedItemByMouse(data, game, event, data.musicItem);
		}
	}

	void UpdateGameStateOptions(GameStateOptionsData& data, const Game& game)
	{
		bool isSound = (static_cast<std::uint8_t>(game.options) & static_cast<std::uint8_t>(GameOptions::Sound)) != 
					   static_cast<std::uint8_t>(GameOptions::Empty);
		data.fieldMarkSoundShape.setTexture(isSound ? &data.checkMarkTexture : &data.crossMarkTexture);

		bool isMusic = (static_cast<std::uint8_t>(game.options) & static_cast<std::uint8_t>(GameOptions::Music)) != 
					   static_cast<std::uint8_t>(GameOptions::Empty);
		data.fieldMarkMusicShape.setTexture(isMusic ? &data.checkMarkTexture : &data.crossMarkTexture);

		if (data.menu.selectedItem == &data.soundItem)
		{
			data.fieldMarkSoundShape.setOutlineColor(sf::Color::Green);
		}
		else
		{
			data.fieldMarkSoundShape.setOutlineColor(sf::Color::White);
		}

		if (data.menu.selectedItem == &data.musicItem)
		{
			data.fieldMarkMusicShape.setOutlineColor(sf::Color::Green);
		}
		else
		{
			data.fieldMarkMusicShape.setOutlineColor(sf::Color::White);
		}
	}

	void DrawGameStateOptions(GameStateOptionsData& data, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 100.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, { viewSize.x / 3.f, viewSize.y * (2.f / 5.f) }, { 0.5f, 0.f });

		data.fieldMarkSoundShape.setPosition({ viewSize.x * 2.f / 3.f, data.soundItem.text.getPosition().y});
		window.draw(data.fieldMarkSoundShape);

		data.fieldMarkMusicShape.setPosition({ viewSize.x * 2.f / 3.f, data.musicItem.text.getPosition().y });
		window.draw(data.fieldMarkMusicShape);
	}

	void RunSelectedItem(GameStateOptionsData& data, Game& game)
	{
		PlayGameSounds(game.sound, static_cast<uint8_t>(game.options), SoundOption::Enter);
		if (data.menu.selectedItem == &data.soundItem)
		{
			game.options = (GameOptions)(static_cast<std::uint8_t>(game.options) ^ static_cast<std::uint8_t>(GameOptions::Sound));
		}
		else if (data.menu.selectedItem == &data.musicItem)
		{
			game.options = (GameOptions)(static_cast<std::uint8_t>(game.options) ^ static_cast<std::uint8_t>(GameOptions::Music));
		}
		else if (data.menu.selectedItem = &data.backItem)
		{
			PopGameState(game);
		}
	}

	void RunSelectedItemByMouse(GameStateOptionsData& data, Game& game, const sf::Event& event, MenuItem& menuItem)
	{
		if (data.menu.selectedItem != &menuItem)
		{
			SelectMenuItem(data.menu, &menuItem);
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