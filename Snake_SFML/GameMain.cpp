#include <SFML/Graphics.hpp>
#include <random>

const sf::String RESOURCES_PATH = "Assets/";

const int SCREEN_WIGHT = 1024;
const int SCREEN_HEIGHT = 768;

const float SNAKE_SIZE = 20.f;
const int SNAKE_SPEED = 150;
const float APPLE_SIZE = 10.f;

typedef sf::Vector2f Position;

enum class SnakeDirection
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
    SnakeDirection direction = SnakeDirection::Left;
    float speed = 0.f;
};

struct Apple
{
    Position position;
    sf::CircleShape shape;
    bool isEaten = false;

};

bool FindSnakeCollisionWithApple(const Position& snakePosition, const Position& applePosition)
{
    float deltaX = snakePosition.x - applePosition.x;
    float deltaY = snakePosition.y - applePosition.y;
    float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
    if (distance < SNAKE_SIZE / 2.f + APPLE_SIZE)
    {
        return true;
    }
    return false;
}

void ResetAppleState(Apple& apple)
{
    apple.position.x = static_cast<float>(rand() % SCREEN_WIGHT);
    apple.position.y = static_cast<float>(rand() % SCREEN_HEIGHT);
}

void RestartGame(Snake& snake, Apple& apple)
{
    snake.position.x = SCREEN_WIGHT / 2.f;
    snake.position.y = SCREEN_HEIGHT / 2.f;
    snake.direction = SnakeDirection::Left;
    ResetAppleState(apple);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIGHT, SCREEN_HEIGHT), "SNAKE");
    
    srand(static_cast<unsigned int>(std::time(nullptr)));

    Snake snake;
    snake.shape.setSize({ SNAKE_SIZE, SNAKE_SIZE });
    snake.shape.setOrigin({ SNAKE_SIZE / 2.f, SNAKE_SIZE / 2.f });
    snake.shape.setFillColor(sf::Color::Green);
    snake.speed = SNAKE_SIZE;
    snake.position.x = SCREEN_WIGHT / 2.f;
    snake.position.y = SCREEN_HEIGHT / 2.f; 

    Apple apple;
    apple.shape.setRadius(APPLE_SIZE);
    apple.shape.setOrigin({ APPLE_SIZE, APPLE_SIZE});
    apple.shape.setFillColor(sf::Color::Red);
    ResetAppleState(apple);

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
            snake.direction = SnakeDirection::Up;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            snake.direction = SnakeDirection::Right;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            snake.direction = SnakeDirection::Down;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            snake.direction = SnakeDirection::Left;
        }

        switch (snake.direction)
        {
        case SnakeDirection::Left:
            snake.position.x -= SNAKE_SPEED * deltaTime;
            break;
        case SnakeDirection::Up:
            snake.position.y -= SNAKE_SPEED * deltaTime;
            break;
        case SnakeDirection::Right:
            snake.position.x += SNAKE_SPEED * deltaTime;
            break;
        case SnakeDirection::Down:
            snake.position.y += SNAKE_SPEED * deltaTime;
            break;
        }

        if (snake.position.x - SNAKE_SIZE / 2.f < 0 || snake.position.x + SNAKE_SIZE / 2.f > SCREEN_WIGHT ||
            snake.position.y - SNAKE_SIZE / 2.f < 0 || snake.position.y + SNAKE_SIZE / 2.f > SCREEN_HEIGHT)
        {
            RestartGame(snake, apple);
        }

        if (FindSnakeCollisionWithApple(snake.position, apple.position))
        {
            ResetAppleState(apple);
        }

        apple.shape.setPosition(apple.position);
        snake.shape.setPosition(snake.position);
        window.clear();
        window.draw(snake.shape);
        window.draw(apple.shape);
        window.display();
    }

    return 0;
}