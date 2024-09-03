#include "UI.h"

namespace SnakeGame
{
	void InitUI(UI& ui, sf::Font font)
	{
		ui.font = font;

		ui.scoreText.setString("0");
		ui.scoreText.setFont(ui.font);
		ui.scoreText.setCharacterSize(static_cast<int>(FIELD_ON_TOP_SCREEN * 0.6));
		ui.scoreText.setFillColor(sf::Color::White);
		
		ui.line.setSize({ SCREEN_WIDHT, 2.f });
		ui.line.setFillColor(sf::Color::White);
		ui.line.setOrigin({ 0, ui.line.getSize().y / 2.f});
		ui.line.setPosition({ 0, FIELD_ON_TOP_SCREEN });

		ui.pauseText.setString("||");
		ui.pauseText.setFont(ui.font);
		ui.pauseText.setCharacterSize(static_cast<int>(FIELD_ON_TOP_SCREEN * 0.6));
		ui.pauseText.setFillColor(sf::Color::White);
		ui.pauseText.setOrigin(GetItemOrigin(ui.pauseText, { 0.5f, 0.5f }));
		ui.pauseText.setPosition({ SCREEN_WIDHT - 30.f, static_cast<int>(FIELD_ON_TOP_SCREEN / 2.f) });
	}

	sf::FloatRect GetGlobalBoundsOfPauseButton(UI& ui)
	{
		return ui.pauseText.getGlobalBounds();
	}

	void UpdateUI(UI& ui, unsigned int score)
	{
		ui.scoreText.setString(std::to_string(score));
	}

	void DrawUI(UI& ui, sf::RenderWindow& window)
	{
		ui.scoreText.setOrigin(GetItemOrigin(ui.scoreText, { 1.f, 0.5f }));
		ui.scoreText.setPosition({ SCREEN_WIDHT - 80.f, static_cast<int>(FIELD_ON_TOP_SCREEN / 2.f) });
		window.draw(ui.scoreText);
		window.draw(ui.line);
		window.draw(ui.pauseText);
	}
}