#include <SFML/Graphics.hpp>

const sf::String RESOURCES_PATH = "Assets/";

const int SCREEN_WIGHT = 1024;
const int SCREEN_HEIGHT = 768;

const float SNAKE_SIZE = 20.f;
const int SNAKE_SPEED = 150;

typedef sf::Vector2f Position;

enum class PlayerDirection
{
    Left = 0,
    Up,
    Right,
    Down
};

struct Snake
{
    Position position;
    sf::RectangleShape shape;
    PlayerDirection direction = PlayerDirection::Left;
    float speed = 0.f;
};

void RestartGame(Snake& snake)
{
    snake.position.x = SCREEN_WIGHT / 2.f;
    snake.position.y = SCREEN_HEIGHT / 2.f;
    snake.direction = PlayerDirection::Left;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIGHT, SCREEN_HEIGHT), "SNAKE");
    
    Snake snake;
    snake.shape.setSize({ SNAKE_SIZE, SNAKE_SIZE });
    snake.shape.setOrigin({ SNAKE_SIZE / 2.f, SNAKE_SIZE / 2.f });
    snake.shape.setFillColor(sf::Color::Green);
    snake.speed = SNAKE_SIZE;
    snake.position.x = SCREEN_WIGHT / 2.f;
    snake.position.y = SCREEN_HEIGHT / 2.f; 

    sf::Clock gameLock;
    sf::Time lastTime = gameLock.getElapsedTime();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Time currectTime = gameLock.getElapsedTime();
        float deltaTime = currectTime.asSeconds() - lastTime.asSeconds();
        lastTime = currectTime;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            snake.direction = PlayerDirection::Up;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            snake.direction = PlayerDirection::Right;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            snake.direction = PlayerDirection::Down;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            snake.direction = PlayerDirection::Left;
        }

        switch (snake.direction)
        {
        case PlayerDirection::Left:
            snake.position.x -= SNAKE_SPEED * deltaTime;
            break;
        case PlayerDirection::Up:
            snake.position.y -= SNAKE_SPEED * deltaTime;
            break;
        case PlayerDirection::Right:
            snake.position.x += SNAKE_SPEED * deltaTime;
            break;
        case PlayerDirection::Down:
            snake.position.y += SNAKE_SPEED * deltaTime;
            break;
        }

        if (snake.position.x - SNAKE_SIZE / 2.f < 0 || snake.position.x + SNAKE_SIZE / 2.f > SCREEN_WIGHT ||
            snake.position.y - SNAKE_SIZE / 2.f < 0 || snake.position.y + SNAKE_SIZE / 2.f > SCREEN_HEIGHT)
        {
            RestartGame(snake);
        }

        snake.shape.setPosition(snake.position.x, snake.position.y);
        window.clear();
        window.draw(snake.shape);
        window.display();
    }

    return 0;
}