#include "Menu.h"
#include <cassert>

namespace SnakeGame
{
	void InitMenuItem(MenuItem& item)
	{
		for (auto& child : item.children)
		{
			child->parent = &item;
			InitMenuItem(*child);
		}
	}

	void SelectMenuItem(Menu& menu, MenuItem* item)
	{
		// It is definitely error to select root item
		assert(item != &menu.rootItem);

		if (menu.selectedItem == item)
		{
			return;
		}

		if (item && !item->isEnabled)
		{
			// Don't allow to select disabled item
			return;
		}

		if (menu.selectedItem)
		{
			menu.selectedItem->text.setFillColor(menu.selectedItem->deselectedColor);
		}

		menu.selectedItem = item;

		if (menu.selectedItem)
		{
			menu.selectedItem->text.setFillColor(menu.selectedItem->selectedColor);
		}
	}

	bool SelectPreviousMenuItem(Menu& menu)
	{
		
		if (menu.selectedItem)
		{
			MenuItem* parent = menu.selectedItem->parent;
			assert(parent); // There always should be parent

			auto it = std::find(parent->children.begin(), parent->children.end(), menu.selectedItem);
			if (it != parent->children.begin())
			{
				SelectMenuItem(menu, *(--it));
				return true;
			}
		}

		return false;
	}

	bool SelectNextMenuItem(Menu& menu)
	{
		if (menu.selectedItem)
		{
			MenuItem* parent = menu.selectedItem->parent;
			assert(parent); // There always should be parent
			auto it = std::find(parent->children.begin(), parent->children.end(), menu.selectedItem);
			if (it != parent->children.end() - 1)
			{
				SelectMenuItem(menu, *(++it));
				return true;
			}
		}
		return false;
	}

	bool ExpandSelectedItem(Menu& menu)
	{
		if (menu.selectedItem && menu.selectedItem->children.size() > 0)
		{
			SelectMenuItem(menu, menu.selectedItem->children.front());
			return true;
		}
		return false;
	}

	bool CollapseSelectedItem(Menu& menu)
	{
		if (menu.selectedItem && menu.selectedItem->parent && menu.selectedItem->parent != &menu.rootItem)
		{
			SelectMenuItem(menu, menu.selectedItem->parent);
			return true;
		}
		return false;
	}

	MenuItem* GetCurrentMenuContext(Menu& menu)
	{
		return menu.selectedItem ? menu.selectedItem->parent : &menu.rootItem;
	}

	void DrawMenu(Menu& menu, sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin)
	{
		MenuItem* expandedItem = GetCurrentMenuContext(menu);

		std::vector<sf::Text*> texts;
		texts.reserve(expandedItem->children.size());
		for (auto& child : expandedItem->children)
		{
			if (child->isEnabled)
			{
				texts.push_back(&child->text);
			}
		}

		DrawItemsList(window, texts, expandedItem->childrenSpacing, expandedItem->childrenOrientation,
			expandedItem->childrenAlignment, position, origin);
	}

	void SetTextParametrs(sf::Text& itemText, const std::string title, sf::Font& font, const int size, sf::Color color)
	{
		itemText.setString(title);
		itemText.setFont(font);
		itemText.setCharacterSize(size);
		if (color != sf::Color::Transparent)
		{
			itemText.setFillColor(color);
		}
	}

	void PlayEnterSoundMenu(Menu& menu)
	{
		assert(menu.buffer.loadFromFile(RESOURCES_PATH + "Sound/Timgormly_Enter.wav"));
		menu.enterSound.setBuffer(menu.buffer);
		menu.enterSound.setVolume(SOUND_VOLUME);
		menu.enterSound.play();
	}

	void PlayHoverSoundMenu(Menu& menu)
	{
		assert(menu.buffer.loadFromFile(RESOURCES_PATH + "Sound/Theevilsocks__menu-hover.wav"));
		menu.hoverSound.setBuffer(menu.buffer);
		menu.hoverSound.setVolume(SOUND_VOLUME);
		menu.hoverSound.play();
	}
}
