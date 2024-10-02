#include "InputFields.h"


namespace SnakeGame
{
    void InitInputFields(InputFields& fields, const sf::Font& font, const std::vector<char>& standartName)
    {
        fields.fields.resize(MAX_SYMBOLS_IN_NAME);
        for (auto& it : fields.fields)
        {
            it.field.setSize({INPUT_FIELD_WIDHT, INPUT_FIELD_HEIGHT});
            it.field.setFillColor(sf::Color::Black);
            it.field.setOutlineThickness(1.f);
            it.field.setOutlineColor(sf::Color::White);
            it.field.setOrigin({ 0, it.field.getSize().y / 2.f } );

            it.letter.setFont(font);
            it.letter.setCharacterSize(CHARACTER_SIZE_INPUT_FIELD);
            it.letter.setFillColor(sf::Color::White);
            it.letter.setOrigin(GetItemOrigin(it.letter, { 0.5f, 0.5f }));
        }

        int index = 0;
        for (auto& it : fields.fields)
        {
            if (index < standartName.size())
            {
                it.letter.setString(std::to_string(standartName[index]));
            }
        }
    }

    void UpdateInputFields(InputFields& fields, const std::vector<char>& newName)
    {
        for (auto& it : fields.fields)
        {
            it.letter.setString("");
        }

        int index = 0;
        for (auto& it : fields.fields)
        {
            if (index < newName.size())
            {
                it.letter.setString(newName[index]);
                ++index;
            }
        }
    }

    void DrawInputFields(InputFields& fields, sf::RenderWindow& window, const Position positionMindleField)
    {
        sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

        float posFirstFieldX = positionMindleField.x - ((static_cast<float>(INPUT_FIELD_WIDHT + SPACING_BETWEEN_INPUT_FIELDS) * 
                               fields.fields.size()) - SPACING_BETWEEN_INPUT_FIELDS) / 2.f;

        for (auto& it : fields.fields)
        {
            it.field.setPosition({ posFirstFieldX, positionMindleField.y });
            posFirstFieldX += (INPUT_FIELD_WIDHT + SPACING_BETWEEN_INPUT_FIELDS);
            it.letter.setOrigin(GetItemOrigin(it.letter, { 0.5f, 0.5f }));
            it.letter.setPosition({ it.field.getPosition().x + INPUT_FIELD_WIDHT / 2.f, it.field.getPosition().y});
        }

        for (auto& it : fields.fields)
        {
            window.draw(it.field);
            window.draw(it.letter);
        }
    }
}