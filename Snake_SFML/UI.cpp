#include "UI.h"

namespace SnakeGame
{
	void InitUI(UI& ui, const sf::Font font)
	{
		ui.font = font;

		ui.scoreText.setString("0");
		ui.scoreText.setFont(ui.font);
		ui.scoreText.setCharacterSize(CHARACTER_SIZE_SCORE);
		ui.scoreText.setFillColor(sf::Color::White);
		
		ui.line.setSize({ SCREEN_WIDHT, 2.f });
		ui.line.setFillColor(sf::Color::White);
		ui.line.setOrigin({ 0, ui.line.getSize().y / 2.f});
		ui.line.setPosition({ 0, FIELD_ON_TOP_SCREEN });

		ui.pauseButtonText.setString("||");
		ui.pauseButtonText.setFont(ui.font);
		ui.pauseButtonText.setCharacterSize(CHARACTER_SIZE_SCORE);
		ui.pauseButtonText.setFillColor(sf::Color::White);
		ui.pauseButtonText.setOrigin(GetItemOrigin(ui.pauseButtonText, { 0.5f, 0.5f }));
		ui.pauseButtonText.setPosition({ SCREEN_WIDHT - 30.f, static_cast<int>(FIELD_ON_TOP_SCREEN / 2.f) });

		ui.timeAtBeginningText.setString(std::to_string(static_cast<int>(ui.timeAtBeginning)));
		ui.timeAtBeginningText.setFont(ui.font);
		ui.timeAtBeginningText.setCharacterSize(60);
		ui.timeAtBeginningText.setFillColor(sf::Color::White);
	}

	void UpdatePauseTimeUI(UI& ui, const float deltaTime)
	{
		if (ui.timeAtBeginning > 0)
		{
			ui.timeAtBeginning -= deltaTime;
		}
		ui.timeAtBeginningText.setString(std::to_string(static_cast<int>(ui.timeAtBeginning)));
	}

	void UpdateScoreUI(UI& ui, const int score)
	{
		ui.scoreText.setString(std::to_string(score));
	}

	void DrawUI(UI& ui, sf::RenderWindow& window)
	{
		ui.scoreText.setOrigin(GetItemOrigin(ui.scoreText, { 1.f, 0.5f }));
		ui.scoreText.setPosition({ SCREEN_WIDHT - 80.f, static_cast<int>(FIELD_ON_TOP_SCREEN / 2.f) });
		window.draw(ui.scoreText);
		window.draw(ui.line);
		window.draw(ui.pauseButtonText);

		ui.timeAtBeginningText.setOrigin(GetItemOrigin(ui.timeAtBeginningText, { 0.5f, 0.5f }));
		ui.timeAtBeginningText.setPosition({ SCREEN_WIDHT / 2.f, SCREEN_HEIGHT / 3.f });
		if (ui.timeAtBeginning > 0)
		{
			window.draw(ui.timeAtBeginningText);
		}
	}

	void ReturnOriginalPauseTime(UI& ui)
	{
		ui.timeAtBeginning = PAUSE_AT_BEGINNING;
	}
}