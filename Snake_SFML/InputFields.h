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
		std::vector<LetterInputField*> fields;
	};
	
	void InitInputFields(InputFields& fields, sf::Font& font);
	void UpdateInputFields(InputFields& fields, std::vector<char> newName);
	void DrawInputFields(InputFields& fields, sf::RenderWindow& window, const Position positionCenterField);
}
