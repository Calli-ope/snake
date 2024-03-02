#include "headers/GamePlay.h"
#include <SFML/Window/Event.hpp>

GamePlay::GamePlay(std::shared_ptr<Context>& context)
    : m_context(context),
        m_direction({16.f, 0.f}),
        m_elapsedTime(sf::Time::Zero)
{
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

    m_border[0].setTextureRect({0, 0, m_context->m_window->getSize().x, 16});
    m_border[1].setTextureRect({0, 0, m_context->m_window->getSize().x, 16});
    m_border[1].setPosition(0, m_context->m_window->getSize().y - 16);

    m_border[2].setTextureRect({0, 0, 16, m_context->m_window->getSize().y});
    m_border[3].setTextureRect({0, 0, 16, m_context->m_window->getSize().y});
    m_border[3].setPosition(m_context->m_window->getSize().x - 16, 0);

    //display food
    m_food.setTexture(m_context->m_assets->GetTexture(FOOD));
    m_food.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);

    //display snake
    m_snake.Init(m_context->m_assets->GetTexture(SNAKE));
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
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                m_direction = {0.f, -16.f};
                break;
            case sf::Keyboard::Down:
                m_direction = {0.f, 16.f};
                break;
            case sf::Keyboard::Left:
                m_direction = {-16.f, 0.f};
                break;
            case sf::Keyboard::Right:
                m_direction = {16.f, 0.f};
                break;

            default:
                break;
            }
        }
    }
}

void GamePlay::Update(sf::Time deltaTime)
{
    m_elapsedTime += deltaTime;

    if (m_elapsedTime.asSeconds() > 0.1)
    {
        m_snake.Move(m_direction);
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

    m_context->m_window->display();
}

void GamePlay::Pause()
{

}

void GamePlay::Start()
{

}