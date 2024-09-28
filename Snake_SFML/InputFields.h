#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Math.h"

namespace SnakeGame
{
	struct LetterInputField
	{
		sf::Text letter;
		sf::RectangleShape field;
	};

	struct InputFields
	{
		std::vector<LetterInputField> fields;
	};
	
	void InitInputFields(InputFields& fields, const sf::Font& font, const std::vector<char>& standartName);
	void UpdateInputFields(InputFields& fields, const std::vector<char>& newName);
	void DrawInputFields(InputFields& fields, sf::RenderWindow& window, const Position positionMindleField);
}
