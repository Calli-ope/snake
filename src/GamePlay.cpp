#include "headers/GamePlay.h"
#include "headers/GameOver.h"
#include <SFML/Window/Event.hpp>

#include <cstdlib>
#include <ctime>

GamePlay::GamePlay(std::shared_ptr<Context>& context)
    : h_context(context),
      h_direction({24.f, 0.f}),
      h_elapsedTime(sf::Time::Zero),
      h_score(0)
{
    srand(time(nullptr));
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
    //get assets
    h_context->h_assets->AddTexture(BACKGROUND, "assets/background.png", true);
    h_context->h_assets->AddTexture(BORDER, "assets/border.png", true);
    h_context->h_assets->AddTexture(FOOD, "assets/food.png");
    h_context->h_assets->AddTexture(SNAKE, "assets/snake.png");

    //display background
    h_background.setTexture(h_context->h_assets->GetTexture(BACKGROUND));
    h_background.setTextureRect(h_context->h_window->getViewport(h_context->h_window->getDefaultView()));

    //display border
    for (auto& border : h_border)
    {
        border.setTexture(h_context->h_assets->GetTexture(BORDER));
    }

    h_border[0].setTextureRect({0, 0, static_cast<int>(h_context->h_window->getSize().x), 24});
    h_border[1].setTextureRect({0, 0, static_cast<int>(h_context->h_window->getSize().x), 24});
    h_border[1].setPosition(0, h_context->h_window->getSize().y - 24);

    h_border[2].setTextureRect({0, 0, 24, static_cast<int>(h_context->h_window->getSize().y)});
    h_border[3].setTextureRect({0, 0, 24, static_cast<int>(h_context->h_window->getSize().y)});
    h_border[3].setPosition(h_context->h_window->getSize().x - 24, 0);

    //display food
    h_food.setTexture(h_context->h_assets->GetTexture(FOOD));
    h_food.setPosition(h_context->h_window->getSize().x / 2, h_context->h_window->getSize().y / 2);

    //display snake
    h_snake.Init(h_context->h_assets->GetTexture(SNAKE));

    //display score
    h_scoreLabel.setFont(h_context->h_assets->GetFont(FONT));
    h_scoreLabel.setString("Score: " + std::to_string(h_score));
    h_scoreLabel.setCharacterSize(24);
    h_scoreLabel.setFillColor(sf::Color::Yellow);
    h_scoreLabel.setOrigin(h_scoreLabel.getLocalBounds().width / 2, h_scoreLabel.getLocalBounds().height / 2);
    h_scoreLabel.setPosition(h_context->h_window->getSize().x / 2, h_context->h_window->getSize().y / 2 - 240.f);
}

void GamePlay::ProcessInput()
{
    sf::Event event;
    while (h_context->h_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            h_context->h_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            sf::Vector2f newDirection = h_direction;
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                newDirection = {0.f, -24.f};
                break;
            case sf::Keyboard::Down:
                newDirection = {0.f, 24.f};
                break;
            case sf::Keyboard::Left:
                newDirection = {-24.f, 0.f};
                break;
            case sf::Keyboard::Right:
                newDirection = {24.f, 0.f};
                break;

            default:
                break;
            }

            if (std::abs(h_direction.x) != std::abs(newDirection.x) ||
                std::abs(h_direction.y) != std::abs(newDirection.y))
            {
                h_direction = newDirection;
            }
        }
    }
}

void GamePlay::Update(sf::Time deltaTime)
{
    h_elapsedTime += deltaTime;

    if (h_elapsedTime.asSeconds() > 0.1)
    {
        for (auto &border : h_border)
        {
            if (h_snake.isOn(border))
            {
                //end the game, when the snake is colliding with the border
                h_context->h_states->Add(std::make_unique<GameOver>(h_context), true);
                break;
            }
        }

        if (h_snake.isOn(h_food))
        {
            //grow the snake, when the snake is on food
            h_snake.Grow(h_direction);

            //randomize new food position
            int x = std::clamp<int>(rand() % (h_context->h_window->getSize().x), 24, h_context->h_window->getSize().x - 2 * 24);
            int y = std::clamp<int>(rand() % (h_context->h_window->getSize().y), 24, h_context->h_window->getSize().y - 2 * 24);
            h_food.setPosition(x, y);

            h_score++;
            h_scoreLabel.setString("Score: " + std::to_string(h_score));
        }
        else
        {
            h_snake.Move(h_direction);
        }

        if (h_snake.isColliding())
        {
            //end the game, when the snake is colliding with itself
            h_context->h_states->Add(std::make_unique<GameOver>(h_context), true);
        }

        h_elapsedTime = sf::Time::Zero;
    }
}

void GamePlay::Draw()
{
    h_context->h_window->clear();

    h_context->h_window->draw(h_background);
    for (auto& border : h_border)
    {
        h_context->h_window->draw(border);
    }
    h_context->h_window->draw(h_food);
    h_context->h_window->draw(h_snake);
    h_context->h_window->draw(h_scoreLabel);

    h_context->h_window->display();
}
