#include "GameStateEnterName.h"
#include "Game.h"
#include <cassert>
#include <string>
#include <unordered_map>

namespace SnakeGame
{
    void InitGameStateEnterName(GameStateEnterNameData& data, Game& game)
    {
        assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Retro-Gaming.ttf"));

        SetTextParametrs(data.menu.rootItem.hintText, "Are you want to enter name?", 
                         data.font, CHARACTER_SIZE_LONG_TITLE, sf::Color::White);
        data.menu.rootItem.childrenOrientation = Orientation::Vertical;
        data.menu.rootItem.childrenAlignment = Alignment::Middle;
        data.menu.rootItem.childrenSpacing = 20.f;
        data.menu.rootItem.children.push_back(&data.noItem);
        data.menu.rootItem.children.push_back(&data.yesItme);

        SetTextParametrs(data.noItem.text, "No", data.font, CHARACTER_SIZE_INIT_MENU);
        SetTextParametrs(data.yesItme.text, "Yes", data.font, CHARACTER_SIZE_INIT_MENU);
        SetTextParametrs(data.yesItme.hintText, "Enter name", data.font, CHARACTER_SIZE_DEFAULT_TITLE, sf::Color::White);
        data.yesItme.children.push_back(&data.enterItem);

        SetTextParametrs(data.enterItem.text, "Enter", data.font, CHARACTER_SIZE_INIT_MENU);

        InitMenuItem(data.menu.rootItem);
        SelectMenuItem(data.menu, &data.noItem);

        // default name
        data.inputLetters.push_back('X');
        data.inputLetters.push_back('Y');
        data.inputLetters.push_back('Z');

        InitInputFields(data.inputFields, data.font, data.inputLetters);
        
        for (auto& it : game.recordsTable)
        {
            data.newRecordsTable.push_back({ it.first, it.second });
        }
    }

    void ShutdownGameStateEnterName(GameStateEnterNameData& data, Game& game)
    {
        for (auto it : data.inputLetters)
        {
            data.newName.push_back(it);
        }
        data.newRecordsTable.push_back({ data.newName, game.gameScore });

        auto cmp = [](std::pair<std::string, int>& left, std::pair<std::string, int>& right)
            {
                return left.second > right.second;
            };
        std::sort(data.newRecordsTable.begin(), data.newRecordsTable.end(), cmp);

        std::unordered_multimap<std::string, int> recordsTable;

        int score = 0;
        for (auto it = data.newRecordsTable.begin(); it != data.newRecordsTable.end(); ++it)
        {
            if (score > RECORDS_TABLE_SIZE_IN_LEADER_BOARD)
            {
                break;
            }
            recordsTable.insert({ it->first, it->second });
            ++score;
        }

        game.recordsTable = recordsTable;

        SerializeGame(game);
    }

    void HandleGameStateEnterNameWindowEvent(GameStateEnterNameData& data, Game& game, const sf::Event& event, const sf::Vector2i mousePosition)
    {
        if (!data.menu.selectedItem)
        {
            return;
        }

        if (data.menu.selectedItem == &data.enterItem)
        {
            if (!data.isClearedDefaultName && IsAllowSymbol(event))
            {
                data.inputLetters.clear();
                data.isClearedDefaultName = true;
            }

            if (event.type == sf::Event::TextEntered)
            {
                if (IsAllowSymbol(event) && data.inputLetters.size() < MAX_SYMBOLS_IN_NAME)
                {
                    data.inputLetters.push_back(toupper(static_cast<char>(event.text.unicode)));
                    PlayGameSounds(game.sound, static_cast<uint8_t>(game.options), SoundOption::Hover);
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::BackSpace && !data.inputLetters.empty())
                {
                    data.inputLetters.pop_back();
                    PlayGameSounds(game.sound, static_cast<uint8_t>(game.options), SoundOption::Hover);
                }
            }
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::B)
            {
                CollapseSelectedItem(data.menu);
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
                if (data.menu.selectedItem != child)
                {
                    SelectMenuItem(data.menu, child);
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
    }

    void UpdateGameStateEnterName(GameStateEnterNameData& data)
    {
        if (data.menu.selectedItem == &data.enterItem)
        {
            UpdateInputFields(data.inputFields, data.inputLetters);
        }
    }

    void DrawGameStateEnterName(GameStateEnterNameData& data, sf::RenderWindow& window)
    {
        sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

        sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
        hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
        hintText->setPosition(viewSize.x / 2.f, viewSize.y / 5.f);
        window.draw(*hintText);

        DrawMenu(data.menu, window, { viewSize.x / 2.f, viewSize.y * (4.f / 5.f) }, { 0.5f, 0.f });
        if (data.menu.selectedItem == &data.enterItem)
        {
            DrawInputFields(data.inputFields, window, viewSize / 2.f);
        }
    }

    void RunSelectedItem(GameStateEnterNameData& data, Game& game)
    {
        PlayGameSounds(game.sound, static_cast<uint8_t>(game.options), SoundOption::Enter);
        if (data.menu.selectedItem == &data.noItem)
        {
            PopGameState(game);
        }
        else if (data.menu.selectedItem == &data.yesItme)
        {
            ExpandSelectedItem(data.menu);
        }
        else if (data.menu.selectedItem == &data.enterItem)
        {
            PopGameState(game);
        }
    }
}