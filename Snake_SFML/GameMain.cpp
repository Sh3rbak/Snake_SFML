#include <SFML/Graphics.hpp>
#include <random>

#include "Game.h"

using namespace SnakeGame;

int main()
{
	unsigned int seed = static_cast<unsigned int>(std::time(nullptr));
	srand(seed);

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDHT, SCREEN_HEIGHT), "SNAKE");
	
	std::shared_ptr<Game> game = std::make_shared<Game>();
	InitGame(*game);

	sf::Clock gameLock;
	sf::Time lastTime = gameLock.getElapsedTime();

	while (window.isOpen())
	{
		HandleWindowEvents(*game, window);

		if (!window.isOpen())
		{
			break;
		}

		sf::Time currectTime = gameLock.getElapsedTime();
		float deltaTime = currectTime.asSeconds() - lastTime.asSeconds();
		lastTime = currectTime;

		if (UpdateGame(*game, deltaTime))
		{
			window.clear();
			DrawGame(*game, window);
			window.display();
		}
		else
		{
			window.close();
		}

	}
	
	ShutdownGame(*game);

	return 0;
}
