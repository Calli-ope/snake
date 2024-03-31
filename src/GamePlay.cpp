#include "headers/GamePlay.h"
#include "headers/GameOver.h"
#include <SFML/Window/Event.hpp>

#include <cstdlib>
#include <ctime>

GamePlay::GamePlay(std::shared_ptr<Context>& context)
    : m_context(context),
        m_direction({24.f, 0.f}),
        m_elapsedTime(sf::Time::Zero),
        m_score(0)
{
    srand(time(nullptr));
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
    m_context->m_assets->AddTexture(BACKGROUND, "assets/background.png", true);
    m_context->m_assets->AddTexture(BORDER, "assets/border.png", true);
    m_context->m_assets->AddTexture(FOOD, "assets/food.png");
    m_context->m_assets->AddTexture(SNAKE, "assets/snake.png");

    //display background
    m_background.setTexture(m_context->m_assets->GetTexture(BACKGROUND));
    m_background.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

    //display border
    for (auto& border : m_border)
    {
        border.setTexture(m_context->m_assets->GetTexture(BORDER));
    }

    m_border[0].setTextureRect({0, 0, static_cast<int>(m_context->m_window->getSize().x), 24});
    m_border[1].setTextureRect({0, 0, static_cast<int>(m_context->m_window->getSize().x), 24});
    m_border[1].setPosition(0, m_context->m_window->getSize().y - 24);

    m_border[2].setTextureRect({0, 0, 24, static_cast<int>(m_context->m_window->getSize().y)});
    m_border[3].setTextureRect({0, 0, 24, static_cast<int>(m_context->m_window->getSize().y)});
    m_border[3].setPosition(m_context->m_window->getSize().x - 24, 0);

    //display food
    m_food.setTexture(m_context->m_assets->GetTexture(FOOD));
    m_food.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);

    //display snake
    m_snake.Init(m_context->m_assets->GetTexture(SNAKE));

    //display score
    m_scoreLabel.setFont(m_context->m_assets->GetFont(FONT));
    m_scoreLabel.setString("Score: " + std::to_string(m_score));
    m_scoreLabel.setCharacterSize(24);
    m_scoreLabel.setFillColor(sf::Color::Yellow);
    m_scoreLabel.setOrigin(m_scoreLabel.getLocalBounds().width / 2, m_scoreLabel.getLocalBounds().height / 2);
    m_scoreLabel.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 240.f);
}

void GamePlay::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            sf::Vector2f newDirection = m_direction;
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

            if (std::abs(m_direction.x) != std::abs(newDirection.x) ||
                std::abs(m_direction.y) != std::abs(newDirection.y))
            {
                m_direction = newDirection;
            }
        }
    }
}

void GamePlay::Update(sf::Time deltaTime)
{
    m_elapsedTime += deltaTime;

    if (m_elapsedTime.asSeconds() > 0.1)
    {
        for (auto &border : m_border)
        {
            if (m_snake.isOn(border))
            {
                m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
                break;
            }
        }

        if (m_snake.isOn(m_food))
        {
            m_snake.Grow(m_direction);

            int x = 0;
            int y = 0;
            x = std::clamp<int>(rand() % (m_context->m_window->getSize().x), 24, m_context->m_window->getSize().x - 2*24);
            y = std::clamp<int>(rand() % (m_context->m_window->getSize().y), 24, m_context->m_window->getSize().y - 2*24);

            m_food.setPosition(x, y);

            m_score++;
            m_scoreLabel.setString("Score: " + std::to_string(m_score));
        }
        else
        {
            m_snake.Move(m_direction);
        }

        if (m_snake.isColliding())
        {
            m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
        }

        m_elapsedTime = sf::Time::Zero;
    }
}

void GamePlay::Draw()
{
    m_context->m_window->clear();

    m_context->m_window->draw(m_background);
    for (auto& border : m_border)
    {
        m_context->m_window->draw(border);
    }
    m_context->m_window->draw(m_food);
    m_context->m_window->draw(m_snake);
    m_context->m_window->draw(m_scoreLabel);

    m_context->m_window->display();
}
